// players.hpp
//
// Created by Madelyne Goforth 8/3/25
//

#ifndef PLAYERS_HPP
#define PLAYERS_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "Jobs.hpp"
#include "Loans.hpp"
#include "Properties.hpp"

using namespace std;

// Forward declarations to resolve circular dependency
class Job;
class Player;
class Economy;
class Property;

// ----- Player class -----
// Represents a player with name, job title, cash balance, and loans
class Player {
private:
    string playerName;
    Job playerJob; // store the job object
    int playerNumber;
    int cash;
    int income;

    int loansToOthersValue = 0;

    // Property Holdings
    vector<Property> propertyHoldings;
    int propertyHoldingsWorth = 0;

    // Net worth = total assets - total liabilities;
    // ** Later for loans class => banks not able to loan more than 50% of player's total asset value
    // No similar limits for player to player loans
    int totalAssets;
    int totalLiabilities;
    int totalNetWorth;

    bool inJail = false;
    bool bankrupt = false;
    bool insolventBankrupt = false;
    bool unemployed = false;

public:
    // Constructor initializes name, starting cash, default unemployed
    Player(int playerNumber, const string& playerName, int startingCash, const Job& job);

    // Accessors (const)
    const string& getName() const;
    const string& getJobTitle() const;
    int getCash() const;

    bool getInJail() const;
    bool getBankrupt() const;
    bool getInsolventBankrupt() const;
    bool getUnemployed() const;

    // Mutators
    void setJobTitle(const string& newJob);

    void setInJail(bool& status);
    void setBankrupt(bool& status);
    void setInsolventBankrupt(bool& status);
    void setUnemployed(bool& status);

    // Cash transfer/change value
    void addCash(int amount); // add or subtract from cash
    bool hasEnoughCash(int amount) const;

    // Process all loans for this player, paying installments to creditors if possible
    // The vector of players is needed to find creditor objects by name or pointer (optional)
    void processLoans();

    // Display player current status: name, job, cash, loans count
    void displayStatus() const;

    void displayStartingStatus() const;

    // Income
    int getIncome() const;
    void setIncome(int newIncome);

    // Further methods: e.g., apply income for passing Go according to job,
    // handle economic events changing cash, interest rates, etc.
};

#endif // PLAYERS_HPP
