//
//  Loans.hpp
//  Pic 10A??
//
//  Created by Madelyne Goforth on 8/29/25.
//

#ifndef LOANS_HPP
#define LOANS_HPP

#include <iostream>
#include "Players.hpp"
#include <cmath>

enum class LoanType { Bank, PlayerToPlayer };
enum class TermType { PerTurn, PerPassGo };

class Loan {
private:
    LoanType type;
    int principal;
    double interestRate;
    int termRemaining;
    TermType termType;
    int paymentPerTerm;
    bool autoPayment;
    int creditorId; // index in players vector or -1 = bank
    int debtorId;   // index in players vector
    bool active;

public:
    Loan(LoanType t, int amount, double rate, int term, TermType tt, bool autoPay,
         int creditor, int debtor)
        : type(t), principal(amount), interestRate(rate), termRemaining(term),
          termType(tt), autoPayment(autoPay), creditorId(creditor), debtorId(debtor), active(true)
    {
        paymentPerTerm = (term > 0) ? static_cast<int>(std::ceil(amount / term)) : amount;
    }

    bool isActive() const { return active; }
    int getCreditorId() const { return creditorId; }
    int getDebtorId() const { return debtorId; }
    LoanType getType() const { return type; }
    int getPaymentPerTerm() const { return paymentPerTerm; }
    int getRemainingTerm() const { return termRemaining; }
    bool isAutoPayment() const { return autoPayment; }

    void processTurn(class GameManager& gm, bool passGoEvent = false);
    bool payExtra(class Player& payer, int amount);
    void display() const;
};

#endif // LOANS_HPP
