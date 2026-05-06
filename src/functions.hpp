#pragma once
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstddef>

// ANSI Colors
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"
#define BOLD    "\033[1m"
#define GREEN   "\033[32m"
#define MAGENTA "\033[35m"

struct Symbol
{
    std::string name;
    std::vector<int> payouts; // index = number of matching reels (0..3)
    int weight;               // higher = more common on reels
};

// payouts[n] = multiplier when n reels match your chosen symbol
// weights control how often each symbol lands (out of total 100)
inline std::vector<Symbol> symbols =
{
    {"Wild",         {0, 10, 40, 200}, 2},   // very rare
    {"Man",          {0, 8,  30, 100}, 3},
    {"Woman",        {0, 6,  20, 75},  5},
    {"Dog",          {0, 6,  20, 75},  5},
    {"Bag of Money", {0, 5,  15, 50},  8},
    {"Bell",         {0, 5,  15, 50},  8},
    {"A",            {0, 4,  10, 30},  12},
    {"K",            {0, 3,  8,  20},  14},
    {"Q",            {0, 3,  8,  20},  14},
    {"J",            {0, 2,  5,  15},  14},
    {"10",           {0, 2,  5,  15},  15},
};

enum Symbolsrank 
{
    WILD, 
    MAN, 
    WOMAN, 
    DOG, 
    BAG_OF_MONEY, 
    BELL, 
    A, 
    K, 
    Q, 
    J, 
    TEN
};

inline void title() 
{
    std::cout << GREEN << R"(
  _________.____    ___________________    _____      _____  _________   ___ ___ .___ _______  ___________
 /   _____/|    |   \_____  \__    ___/   /     \    /  _  \ \_   ___ \ /   |   \|   |\      \ \_   _____/
 \_____  \ |    |    /   |   \|    |     /  \ /  \  /  /_\  \/    \  \//    ~    \   |/   |   \ |    __)_ 
 /        \|    |___/    |    \    |    /    Y    \/    |    \     \___\    Y    /   /    |    \|        \
/_______  /|_______ \_______  /____|    \____|__  /\____|__  /\______  /\___|_  /|___\____|__  /_______  /
        \/         \/       \/                  \/         \/        \/       \/             \/        \/ 
)" << std::endl; 
};

// Weighted RNG: symbols with higher weight appear more often
inline Symbol Reelsrng() 
{
    static std::mt19937 gen(std::random_device{}());

    // Build a weighted distribution from symbol weights
    std::vector<int> weights;
    weights.reserve(symbols.size());
    for (const auto& s : symbols)
        weights.push_back(s.weight);

    std::discrete_distribution<> dist(weights.begin(), weights.end());
    return symbols[static_cast<std::size_t>(dist(gen))];
}