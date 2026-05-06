#include "functions.hpp"

int main()
{
    title();

    int balance = 1000;
    std::cout << GREEN << "Balance: $" << balance << RESET << "\n\n";

    while (balance > 0)
    {
        int bet;
        std::string choice;

        // Bet input
        while (true)
        {
            std::cout << GREEN << "How much do you want to bet? " << RESET;

            if (!(std::cin >> bet))
            {
                std::cout << RED "Invalid input!\n" RESET;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            if (bet <= 0 || bet > balance)
            {
                std::cout << RED << "Invalid bet!\n" << RESET;
                continue;
            }

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }

        // Symbol selection
        Symbolsrank selected;

        while (true)
        {
            std::cout << GREEN << "What do you want to bet on? (Wild, Man, Woman, Dog, Bag, Bell, A, K, Q, J, 10): " << RESET;
            std::getline(std::cin, choice);

            if (choice == "Wild") { selected = WILD; break; }
            if (choice == "Man")  { selected = MAN;  break; }
            if (choice == "Woman"){ selected = WOMAN; break; }
            if (choice == "Dog")  { selected = DOG;  break; }
            if (choice == "Bag")  { selected = BAG_OF_MONEY; break; }
            if (choice == "Bell") { selected = BELL; break; }
            if (choice == "A")    { selected = A;    break; }
            if (choice == "K")    { selected = K;    break; }
            if (choice == "Q")    { selected = Q;    break; }
            if (choice == "J")    { selected = J;    break; }
            if (choice == "10")   { selected = TEN;  break; }

            std::cout << RED << "Invalid choice, try again.\n" << RESET;
        }

        // Spin 3 reels
        Symbol reel1 = Reelsrng();
        Symbol reel2 = Reelsrng();
        Symbol reel3 = Reelsrng();

        std::cout << CYAN << reel1.name << " || " << reel2.name << " || " << reel3.name << RESET << "\n";

        // Count how many reels match the selected symbol
        const std::string& target = symbols[static_cast<std::size_t>(selected)].name;
        int matches = (reel1.name == target) + (reel2.name == target) + (reel3.name == target);

        int multiplier = symbols[static_cast<std::size_t>(selected)].payouts[matches];

        if (multiplier > 0)
        {
            int winnings = bet * multiplier;
            std::cout << GREEN << "You Win! x" << multiplier << " = $" << winnings << "\n" << RESET;
            balance += winnings;
        }
        else
        {
            std::cout << RED << "You Lose!\n" << RESET;
            balance -= bet;
        }

        std::cout << GREEN << "Balance: $" << balance << RESET << "\n\n";

        if (balance <= 0)
        {
            std::cout << RED << "You're out of money! Game over.\n" << RESET;
            break;
        }

        // Ask to play again
        std::string again;
        while (true)
        {
            std::cout << YELLOW << "Play another round? (y/n): " << RESET;
            std::getline(std::cin, again);
            if (again == "y" || again == "Y") break;
            if (again == "n" || again == "N")
            {
                std::cout << CYAN << "Thanks for playing! Final balance: $" << balance << RESET << "\n";
                return 0;
            }
            std::cout << RED << "Please enter y or n.\n" << RESET;
        }
    }

    return 0;
}