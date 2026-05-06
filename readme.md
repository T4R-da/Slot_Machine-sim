# Slot Machine

A terminal-based slot machine game written in C++17. Spin 3 reels, match your chosen symbol, and multiply your bet.

---

## Building

```bash
g++ -std=c++17 -o slot main.cpp
./slot
```

Requires a C++17-compatible compiler (GCC 7+, Clang 5+). ANSI color codes are used for output — works on Linux, macOS, and Windows Terminal.

---

## How to Play

1. The game starts you with **$1000**.
2. Each round you enter a **bet amount** (must be between $1 and your current balance).
3. Pick a **symbol** to bet on from the list below.
4. Three reels spin — each reel independently lands on a weighted random symbol.
5. Your payout depends on **how many reels match** your chosen symbol.
6. After each round you can choose to play again or quit.
7. The game ends automatically if your balance reaches $0.

---

## Symbols & Payouts

Payouts are shown as bet multipliers (e.g. x10 on a $50 bet = $500 won).

| Symbol        | 1 Match | 2 Matches | 3 Matches | Rarity   |
|---------------|---------|-----------|-----------|----------|
| Wild          | x10     | x40       | x200      | Very rare |
| Man           | x8      | x30       | x100      | Rare     |
| Woman         | x6      | x20       | x75       | Uncommon |
| Dog           | x6      | x20       | x75       | Uncommon |
| Bag of Money  | x5      | x15       | x50       | Common   |
| Bell          | x5      | x15       | x50       | Common   |
| A             | x4      | x10       | x30       | Common   |
| K             | x3      | x8        | x20       | Common   |
| Q             | x3      | x8        | x20       | Common   |
| J             | x2      | x5        | x15       | Common   |
| 10            | x2      | x5        | x15       | Most common |

0 matches on any symbol loses your bet.

---

## Symbol Weights

Symbols are not equally likely — rarer symbols land less often. The RNG uses `std::discrete_distribution` with the following weights out of 100:

| Symbol        | Weight | Approx. chance per reel |
|---------------|--------|--------------------------|
| Wild          | 2      | 2%                       |
| Man           | 3      | 3%                       |
| Woman         | 5      | 5%                       |
| Dog           | 5      | 5%                       |
| Bag of Money  | 8      | 8%                       |
| Bell          | 8      | 8%                       |
| A             | 12     | 12%                      |
| K             | 14     | 14%                      |
| Q             | 14     | 14%                      |
| J             | 14     | 14%                      |
| 10            | 15     | 15%                      |

---

## Project Structure

```
.
├── main.cpp        # Game loop, input handling, round logic
└── functions.hpp   # Symbol definitions, RNG, ANSI colors, title screen
```

---

## Adding Symbols

To add a new symbol, open `functions.hpp` and:

1. Add an entry to the `symbols` vector with a name, payout array `{0, x1, x2, x3}`, and a weight.
2. Add a corresponding entry to the `Symbolsrank` enum in the same position.
3. Add an input branch in the symbol selection loop in `main.cpp`.