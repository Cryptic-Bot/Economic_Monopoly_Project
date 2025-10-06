// Economy.hpp
// Pic 10A??
//
// Created by Madelyne Goforth on 8/11/25.
//

#ifndef ECONOMY_HPP
#define ECONOMY_HPP

#include "Players.hpp"
#include <random>
#include <map>
#include <ctime>
#include <string>
#include <vector>

class Economy {
public:
    string scale;

    // Economic Measures: GDP components
    double consumption;           // C
    double investment;            // I
    double governmentSpending;    // G
    double netExports;            // NX
    double gdp;                   // GDP = C + I + G + NX

    // Unemployment rate (%)
    double unemploymentRate;

    // Inflation broken down into components
    double cpiInflationRate;      // Consumer Price Index inflation (%)
    double ppiInflationRate;      // Producer Price Index inflation (%)
    double gdpDeflator;           // GDP deflator (%)
    double aggregateInflationRate; // Aggregate inflation rate (calculated or base index)

    // Business Confidence Index (0-100 scale)
    double businessConfidence;

    // Federal Reserve Policy Tools
    double federalFundsRate;
    double onRRP;
    double discountRate;
    double interestOnReserves;
    bool quantitativeEasing;

    // Property market variables
    double averagePropertyPrice;      // Average price level of Monopoly properties
    double propertyPriceIndex;        // Index to represent property price changes, base 100
    double constructionCostIndex;     // Index for cost to build houses/hotels, base 100

    // Player income modification parameters
    // Base incomes per job class (map job class to income)
    std::map<std::string, double> baseIncomeByJobClass;

    // Random number generator
    std::mt19937 rng;

    Economy();

    // Update GDP based on components
    void updateGDP();

    // Aggregate inflation calculation based on CPI, PPI, and GDP deflator components
    void updateAggregateInflation();

    // Calculate ripple effects after updates in any metrics
    void propagateEffects();

    // Random event trigger
    void triggerRandomEvent();

    // Event handlers
    void consumerConfidenceBoom();
    void investmentShock();
    void fiscalStimulus();
    void tradeWar();
    void inflationShock();
    void federalReservePolicyChange();
    void bankCrisis();
    void naturalDisaster();
    void housingBubble();
    void supplyChainDisruption();
    void taxChange();
    void productivityInnovation();
    void laborStrike();

    // Update property market prices based on economy state
    void updatePropertyMarketPrices();

    // Update construction costs and activity based on economy state
    void updateConstructionMarket();

    // Utility function to generate random double within a range
    double randomDouble(double min, double max);

    // Display current economic state
    void displayState() const;

    double calculatePlayerIncome(const std::string& jobClass, double baseSalary, bool& unemployedFlag);

    // New members in Economy class
    double bankInterestRate;

    // Event probability system
    std::map<std::string, double> baseEventProb;
    std::map<std::string, std::vector<std::pair<std::string, double>>> eventInfluence;
    std::map<std::string, int> eventCount; // track occurrences

    // New methods
    void initEventSystem(); // set up base probabilities/influence map
    std::string selectWeightedRandomEvent();
    void updateEventProbabilities(); // uses influence from past events
    void updateBankInterestRate();

    bool checkPlayerMonopoly(int playerID, const std::string& sector);
    void updateMonopolyEffects();
};

// Implementation notes:

// - The property market (averagePropertyPrice and propertyPriceIndex) responds to GDP, business confidence, interest rates, inflation, etc
// - Construction costs (constructionCostIndex) reflect inflation measures, supply chain disruptions, and Fed policy influencing borrowing costs.
// - Player income is adjusted from a base income (per job class) by inflation (CPI mainly) and potentially other factors like unemployment or economic booms.
// - Inflation components (CPI, PPI, GDP deflator): CPI affects consumer prices and player income, PPI affects production/construction costs, GDP deflator ties to overall price level changes in GDP.
// - Ripple effects => realistic ish macro; e.g., rising interest rates may depress investment and property prices, raising unemployment.

struct MonopolyInfo {
    string sector;
    double threshold; // % needed for monopoly
};

extern std::map<int, std::map<std::string, double>> playerMarketShare;
// playerID -> {sector -> % share}

extern std::vector<MonopolyInfo> monopolySectors;

#endif // ECONOMY_HPP


