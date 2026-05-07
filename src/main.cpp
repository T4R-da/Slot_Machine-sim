#define MINIAUDIO_IMPLEMENTATION
#include "functions.hpp"
#include <limits>

int main()
{
    ma_result result;
    ma_engine engine;
    ma_sound bgSound;      
    bool audioEnabled = false; 

    result = ma_engine_init(NULL, &engine);
    if (result == MA_SUCCESS) {
        // Start background music looping
        if (ma_sound_init_from_file(&engine, "sound.wav", MA_SOUND_FLAG_STREAM, NULL, NULL, &bgSound) == MA_SUCCESS) {
            ma_sound_set_looping(&bgSound, true);
            ma_sound_start(&bgSound);
            audioEnabled = true;
        }
    }

    Title();

    int balance = 1000;
    std::cout << GREEN << "Balance: $" << balance << RESET << "\n\n";

    while (balance > 0)
    {
        int bet;
        while (true)
        {
            std::cout << GREEN << "How much do you want to bet? " << RESET;
            if (!(std::cin >> bet))
            {
                std::cout << RED << "Invalid input!\n" << RESET;
                std::cin.clear();
                std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
                continue;
            }
            if (bet <= 0 || bet > balance)
            {
                std::cout << RED << "Invalid bet!\n" << RESET;
                continue;
            }
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            break;
        }

        balance -= bet;

        // Play spin sound and animation
        if (audioEnabled) ma_engine_play_sound(&engine, "spin.wav", NULL);
        rollAnimation();

        // Generate actual results
        Symbol reel1 = Reelsrng();
        Symbol reel2 = Reelsrng();
        Symbol reel3 = Reelsrng();

        // Display Final Result clearly
        std::cout << BOLD << "FINAL RESULT:" << RESET << "\n";
        std::cout << GREEN << ">> [ " << reel1.name << " ] [ " 
                  << reel2.name << " ] [ " << reel3.name << " ] <<" << RESET << "\n\n";

        Symbol* payoutSymbol = nullptr;
        int matches = 0;

        for (auto& symbol : symbols)
        {
            if (symbol.name == "Wild") continue;

            bool first  = (reel1.name == symbol.name || reel1.name == "Wild");
            bool second = (reel2.name == symbol.name || reel2.name == "Wild");
            bool third  = (reel3.name == symbol.name || reel3.name == "Wild");

            int currentMatches = 0;
            if (first) {
                currentMatches = 1;
                if (second) {
                    currentMatches = 2;
                    if (third) currentMatches = 3;
                }
            }

            if (currentMatches > matches) {
                matches = currentMatches;
                payoutSymbol = &symbol;
            }
        }

        // Win/Loss Payout and Sound Logic
        if (reel1.name == "Wild" && reel2.name == "Wild" && reel3.name == "Wild")
        {
            if (audioEnabled) ma_engine_play_sound(&engine, "win.wav", NULL);
            int winnings = bet * symbols[WILD].payouts[3];
            std::cout << GREEN << "MEGA JACKPOT! x" << symbols[WILD].payouts[3] << " = $" << winnings << "\n" << RESET;
            balance += winnings;
        }
        else if (payoutSymbol && matches >= 2)
        {
            if (audioEnabled) ma_engine_play_sound(&engine, "win.wav", NULL);
            int multiplier = payoutSymbol->payouts[matches];
            int winnings = bet * multiplier;
            std::cout << GREEN << "You Win! " << payoutSymbol->name << " x" << multiplier << " = $" << winnings << "\n" << RESET;
            balance += winnings;
        }
        else
        {
            if (audioEnabled) ma_engine_play_sound(&engine, "loss.wav", NULL);
            std::cout << RED << "You Lose!\n" << RESET;
        }

        std::cout << GREEN << "Balance: $" << balance << RESET << "\n\n";

        if (balance <= 0) break;

        std::string again;
        while (true)
        {
            std::cout << YELLOW << "Play another round? (y/n): " << RESET;
            std::getline(std::cin, again);
            if (again == "y" || again == "Y") {
                system("cls");
                Title();
                std::cout << GREEN << "Balance: $" << balance << RESET << "\n\n";
                break;
            }
            if (again == "n" || again == "N") {
                std::cout << CYAN << "Thanks for playing! Final balance: $" << balance << RESET << "\n";
                if (audioEnabled) ma_sound_uninit(&bgSound);
                ma_engine_uninit(&engine); 
                return 0;
            }
        }
    }

    if (audioEnabled) ma_sound_uninit(&bgSound);
    ma_engine_uninit(&engine); 
    return 0;
}