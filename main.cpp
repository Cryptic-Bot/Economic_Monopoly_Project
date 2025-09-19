
#include "players.hpp"
#include "gamesettings.hpp"
#include "Menus.hpp"

using namespace std;

int main() {
    // Game intro/Begining text
    GameManager game;
    GameUI graphics;
    if (graphics.beginingtext() == 0) {
        graphics.displayEndScreen();
        return 0;
    }
    
    // Game setup
    // Player settup, job menu, etc.
    if (game.setup() == 0) {
        cout << "Leaving so soon? Buh-bye!" << endl;
        cout << endl;
        graphics.displayEndScreen();
        return 0;
    }
    
    // Gameplay
    MenuFunction menu;
    menu.mainMenu(game);
    
    
    graphics.displayEndScreen();
    return 0;
}

// Add trolling
// Add cussing mode or pro cussing responses
// Job paths? Choose or random? random, choice or choice name/random cash


// turn based
// income for passing go
// random event timer

// Example driver to demonstrate setup and usage
//int main() {
//    // Economy setup
//    Economy economy;
//    economy.triggerEvent(Economy::BOOM);
//
//    // Assign jobs
//    alice.setJobTitle("Banker");
//    bob.setJobTitle("Lawyer");
//
//    // Alice loans Bob $300 with 5% interest for 3 turns
//    Loan loan(300, economy.getInterestRate(), 3, &alice);
//    bob.addLoan(loan);
//
//    // Display initial status
//    alice.displayStatus();
//    bob.displayStatus();
//    std::cout << "\n-- End Turn 1 --\n";
//    
//    // Bob pays interest to Alice
//    bob.processLoans(alice);
//
//    // Display status after one turn
//    alice.displayStatus();
//    bob.displayStatus();
//
//    return 0;
//}


