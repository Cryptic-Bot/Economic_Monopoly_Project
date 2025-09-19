//
//  Menus.hpp
//  Pic 10A??
//
//  Created by Madelyne Goforth on 8/7/25.
//

#ifndef MENUS_HPP
#define MENUS_HPP

#include <iostream>

using namespace std;

class GameManager;
class Player;

class GameUI {
private:
    
    
public:
    int beginingtext();
    
    // Main Menus
    void displayMenu();
    void displayBalanceTransfer();
    void displayViewInfo();
    void displayReportUpdates();
    void displayLoans();
    void displayAssets();
    void displayP2Prelations();
    
    // Job settings menus
    void displayJobMenu(); // Maybe add a more info section later to make the UI neater than whatever the clusterfuck that is
    void displayJobInfoMenu();
    
    // Turns
    void displayGlobalTurn(GameManager& game);
    void displayPlayerTurn(GameManager& game, const vector<Player>& vec);
    
    // Bal Transfer Menus
    void displayBalanceTransferSender (vector<Player> vec);
    void displayBalanceTransferReceiver(vector<Player> vec);
    void displayBalanceTransferConfirmation(const Player& sender, const Player& receiver, int amount);
    
    
    void displayEndScreen();

    
};

#endif // MENUS_HPP

