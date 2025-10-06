//
//  Players.cpp
//  Pic 10A??
//
//  Created by Madelyne Goforth on 8/2/25.
//

#include "Players.hpp"

// Loan Class
// Represents a private loan between players, with principal, interest rate, turns left, and creditor reference
//class Loan {
//private:
//    int principal;
//    double interestRate; // e.g., 0.05f for 5%
//    int turnsLeft;
//    const Player* creditor; // points to creditor player; non-owning
//
//public:
//    // Constructor
//    Loan(int p, float rate, int turns, const Player* cred);
//
//    // Getters (const-qualified)
//    int getPrincipal() const;
//    float getInterestRate() const;
//    int getTurnsLeft() const;
//    const Player* getCreditor() const;
//
//    // Decrement turns left, returns true if loan term ended
//    bool decrementTurn();
//
//    // Calculate interest payment amount for a turn
//    int interestDue() const;
//
//    // Handle loan installment payment from payer to creditor
//    // Return true if payment succeeded, false otherwise
//    bool payInstallment(Player& payer, Player& creditor);
//};

// ----- Player class -----
// Represents a player with name, job title, cash balance, and loans
// Constructor initializes name, starting cash, default unemployed
Player::Player(int playerNumber, const string& playerName, int startingCash, const Job& job) : playerNumber(playerNumber), playerName(playerName), cash(startingCash), playerJob(job), income(job.baseSalary) {}
// Accessors (const)
const string& Player::getName() const {
    return playerName;
}
//const string& Player::getJobTitle() const {
//
//}
int Player::getCash() const {
    return cash;
}
//const vector<Loan>& Player::getLoans() const {
//
//}
//
//    // Mutators
//void Player::setJobTitle(const string& newJob) {
//
//}
//// add or subtract from cash
//void Player::updateCash(int amount) {
//
//}
//    // Loan management
//void Player::addLoan(const Loan& loan) {
//
//}
// Process all loans for this player, paying installments to creditors if possible
// The vector of players is needed to find creditor objects by name or pointer (optional)
//void processLoans();
// Display player current status: name, job, cash, loans count
void Player::displayStatus() const {
    cout << "Player " << playerNumber << ": " << playerName << endl;
    cout << "Job: " << playerJob.name << endl;
    cout << "Current cash: " << cash << endl;
}
void Player::displayStartingStatus() const {
    cout << "Player " << playerNumber << ": " << playerName << endl;
    cout << "Job: " << playerJob.name << endl;
    cout << "Starting income: " << income << endl;
    cout << "Starting cash: " << cash << endl;
}

int Player::getIncome() const { return income; }
void Player::setIncome(int newIncome) { income = newIncome; }
void Player::addCash(int amount) { cash += amount; } // amount can be positive or negative
bool Player::hasEnoughCash(int amount) const { return cash >= amount; }
bool Player::getInJail() const { return inJail; }
bool Player::getBankrupt() const { return bankrupt; }
bool Player::getInsolventBankrupt() const { return insolventBankrupt; }
bool Player::getUnemployed() const { return unemployed; }
void Player::setInJail(bool& status) { inJail = status; }
void Player::setBankrupt(bool& status) { bankrupt = status; }
void Player::setInsolventBankrupt(bool& status) { insolventBankrupt = status; }
void Player::setUnemployed(bool& status) { unemployed = status; }
// Further methods: e.g., apply income for passing Go according to jobw
// handle economic events changing cash, interest rates, etc.


//    // Accessors (const)
//const string& Player::getName() const {
//    
//}
//
//const string& Player::getJobTitle() const {
//    
//}
//
//int Player::getCash() const {
//    
//}
//
//const vector<Loan>& Player::getLoans() const {
//    
//}
//
//    // Mutators
//void Player::setJobTitle(const string& newJob) {
//    
//}
//// add or subtract from cash
//void Player::updateCash(int amount) {
//    
//}
//    // Loan management
//void Player::addLoan(const Loan& loan) {
//    
//}

// Process all loans for this player, paying installments to creditors if possible
// The vector of players is needed to find creditor objects by name or pointer (optional)
//void processLoans();

// ----- Economy class -----
// Represents global economic conditions affecting the game
//class Economy {
//public:
//    enum class Status { Normal, Recession, Boom };
//
//private:
//    Status currentStatus;
//    
//    double interestRate; // base interest rate affecting loans, deposits, etc.
//    double inflationRate;
//    double landRate;
//    double housingRate;
//    double hotelRate;
//
//public:
//    Economy();
//
//    // Set and get economic status
//    void triggerEvent(Status newStatus);
//    Status getStatus() const;
//
//    // Interest rate accessors/mutators
//    float getInterestRate() const;
//    void setInterestRate(float newRate);
//
//    // Return human-readable status as string
//    string statusToString() const;
//};
