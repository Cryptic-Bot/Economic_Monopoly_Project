//
//  Loans.cpp
//  Pic 10A??
//
//  Created by Madelyne Goforth on 8/29/25.
//

#include "Loans.hpp"
#include "gamesettings.hpp"

void Loan::processTurn(GameManager& gm, bool passGoEvent) {
    if (!active) return;

    // Only decrement term in correct event type
    if ((termType == TermType::PerTurn) ||
        (termType == TermType::PerPassGo && passGoEvent)) {

        // Accrue interest
        int interest = static_cast<int>(std::ceil(principal * interestRate));
        principal += interest;

        Player& debtor = gm.modifyPlayersVec()[debtorId];
        Player* creditor = (creditorId >= 0) ? &gm.modifyPlayersVec()[creditorId] : nullptr;

        if (autoPayment && paymentPerTerm > 0) {
            int payment = (paymentPerTerm < principal) ? paymentPerTerm : principal;
            if (debtor.hasEnoughCash(payment)) {
                debtor.addCash(-payment);
                if (creditor) creditor->addCash(payment);
                principal -= payment;
            } else {
                // TODO: mark insufficient funds and alert player outside this function
            }
        }

        termRemaining--;
        if (principal <= 0 || termRemaining <= 0) {
            active = false;
        }
    }
}

// Apply manual extra payment
bool Loan::payExtra(Player& payer, int amount) {
    if (!active || amount <= 0) return false;
    if (!payer.hasEnoughCash(amount)) return false;

    payer.addCash(-amount);
    principal -= amount;
    if (principal <= 0) {
        active = false;
    }
    return true;
}

void Loan::display() const {
    cout << "Loan Type: " << (type == LoanType::Bank ? "Bank" : "PlayerToPlayer") << endl;
    cout << "Principal Remaining: $" << principal << endl;
    cout << "Interest Rate: " << interestRate * 100 << "%" << endl;
    cout << "Term Remaining: " << termRemaining << (termType == TermType::PerTurn ? " turns" : " Go-passes") << endl;
    cout << "Payment per Term: $" << paymentPerTerm << endl;
    cout << "Auto Payment: " << (autoPayment ? "Yes" : "No") << endl;
}
