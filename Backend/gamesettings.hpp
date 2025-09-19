

#ifndef GAMESETTINGS_HPP
#define GAMESETTINGS_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>
#include "Players.hpp"

using namespace std;

class GameManager;
class Player;
class GameUI;

class MenuFunction {
public:
    void mainMenu(GameManager& game);
    void balanceTransferMenu(GameManager& game);
    void viewInfoMenu(GameManager& game);
    void reportUpdatesMenu(GameManager& game);
    void loansMenu(GameManager& game);
    void P2PrelationsMenu(GameManager& game);

    // Jobs Menu
    int jobsMenu(GameManager& game);
};

class GameManager {
private:
    vector<Player> players;
    int nPlayers = 0;
    int globalTurns = 0;
    int nPlayersGone = 0;
    bool allPlayersGone = false;

public:
    int setup();

    // Accessor/Mutator functions for private values
    void setnPlayers(int n);
    int accessnPlayers() const;
    void setGlobalTurns(int n);
    int accessGlobalTurns() const;
    void setnPlayersGone(int n);
    int accessnPlayersGone() const;
    void fillPlayersVec(vector<Player>& vec);
    vector<Player>& modifyPlayersVec();
    const vector<Player>& accessPlayersVec() const;

    bool accessAllPlayersGone() const;
    void setAllPlayersGone(bool& state);
    
    
    
    // Modes
    // Job Settings
    void collectiveEconomy();
    void marketEconomy();
    void meritocracyChoice();
    void incomeVolatility();
    
    // Balance Transfer Menu
    void balanceTransferMenu(GameUI& ui);
    bool confirmTransfer(GameUI& ui, int senderIndex, int receiverIndex, int amount);
    int selectSender(GameUI& ui);
    int selectReceiver(GameUI& ui, int senderIndex);
    int requestTransferAmount();

    Job chooseJobMenu(std::vector<Job>& availableJobs);
    void displayAvailableJobs(const std::vector<Job>& jobs);
};

#endif // GAMESETTINGS_HPP
