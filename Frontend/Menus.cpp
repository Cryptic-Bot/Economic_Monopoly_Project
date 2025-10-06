//
//  Menus.cpp
//  Pic 10A??
//
//  Created by Madelyne Goforth on 8/7/25.
//

#include "Menus.hpp"

int GameUI::beginingtext() {
    cout << "Hello brave entrepreneurs!";
    string dummy;
    getline(cin, dummy); // Pause for Enter key
    cout << "\n";
    
    char userinput;
    cout << "Ready to play \"business\" in the real world? (Y/N): ";
    cin >> userinput;
    while (userinput != 'Y' && userinput != 'y') {
        if (userinput == 'N' || userinput == 'n') {
            cout << "\nSorry to hear that.\nDon't be afraid to try your luck and test your wit next time.\nTa ta for now!\n" << endl;
            return 0;
        }
        else {
            cout <<  "\nInvalid input: Try again.\n";
            cout << "Ready to play \"business\" in the real world? (Y/N): ";
            cin >> userinput;
        }
    }
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear newline from input buffer
    cout << "\n--------------------------------------------\n";
    cout << "\n       Monopoly: Real World Edition\n";
    cout << "                  V 1.0\n\n";
    cout << "--------------------------------------------\n" << endl;
    return 1;
}

// Displays
void GameUI::displayMenu() {
    cout << "=================== Menu ===================" << endl;
    cout << "1. Balance transfer" << endl;
    cout << "2. Display info" << endl;
    cout << "3. Report updates" << endl;
    cout << "4. Loans" << endl;
    cout << "5. Future Update: Assets";
    cout << "6. Future Update: Player to Player Relations" << endl;
    cout << "E. End player turn" << endl;
    cout << "Please enter your choice (1-6, E), Q to quit game: ";
}

void GameUI::displayBalanceTransfer() {
    cout << "============= Balance Transfer =============" << endl;
    cout << "Sender:" << endl;
//    for (auto v : player) {
//        cout << i << ". " << playerName
//    }
    cout << "Please enter your choice (, E), Q to quit game: ";
}

void GameUI::displayViewInfo() {
    cout << "=============== Display Info ===============" << endl;
    
    cout << "Please enter your choice (1-5, E), Q to quit game: ";
}

void GameUI::displayReportUpdates() {
    cout << "============== Report Updates ==============" << endl;
    
    cout << "Please enter your choice (1-5, E), Q to quit game: ";
}

void GameUI::displayLoans() {
    cout << "================ Loans Menu ================" << endl;
    
    cout << "Please enter your choice (1-5, E), Q to quit game: ";
}

void GameUI::displayAssets() {
    
}

void GameUI::displayP2Prelations() {
    cout << "======== Player to Player Relations ========" << endl;
    
    cout << "Please enter your choice (1-5, E), Q to quit game: ";
}

void GameUI::displayJobMenu() {
    cout << "How would you rather the world be?" << endl;
    cout << "======= 1. Collective Economy =======" << endl;
    cout << "======= 2. Market Economy ===========" << endl;
    cout << "======= 3. Meritocracy Choice =======" << endl;
    cout << "======= 4. Income Volatility ========" << endl;
    cout << "======= I. [More info] ==============" << endl;
    cout << "===> Please enter your choice (1-4, I), Q to quit game: ";
}

void GameUI::displayJobInfoMenu() {
    cout << endl;
    cout << "======= 1. *Collective Economy* ======" << endl;
    cout << "     Closest to Std Monopoly: All players earn an equal, fixed income regardless of role or job. This mode emphasizes economic equality and shared prosperity, simulating a system where wealth is evenly distributed." << endl;
    cout << "======= 2. Market Economy ============" << endl;
    cout << "     Players are randomly assigned preset jobs, each with distinct income levels. This mode models a competitive labor market where income varies based on occupation. "<< endl;
    cout << "======= 3. Meritocracy Choice ========" << endl;
    cout << "     Players freely select their jobs from a preset list, balancing income potential against abilities. This mode reflects a society where personal skill and career decisions directly influence earnings." << endl;
    cout << "======= 4. Income Volatility =========" << endl;
    cout << "     Players revieve randomly assigned incomes without job titles, simulating economic unpredictabilty and fluctuating earnings driven by chance." << endl;
    cout << endl;
}

// Turns
// Helper for centering text in a fixed-width banner
std::string centerText(const std::string& text, int width) {
    int len = static_cast<int>(text.size());
    if (len >= width) return text.substr(0, width);
    int padLeft = (width - len) / 2;
    int padRight = width - len - padLeft;
    return std::string(padLeft, ' ') + text + std::string(padRight, ' ');
}

void GameUI::displayGlobalTurn(GameManager& game) {
    const int WIDTH = 44; // total line width to match your example
    std::string headline = "Turn " + std::to_string(game.accessGlobalTurns());
    std::cout << std::string(WIDTH, '-') << std::endl;
    std::cout << "=" << centerText(headline, WIDTH - 2) << "=" << std::endl;
    std::cout << std::string(WIDTH, '-') << std::endl;
}

void GameUI::displayPlayerTurn(GameManager& game, const vector<Player>& vec) {
    const int WIDTH = 44;
    int playerIdx = game.accessnPlayersGone();
    std::string playerBanner;
    if (playerIdx >= 0 && playerIdx < static_cast<int>(vec.size()))
        playerBanner = vec[playerIdx].getName() + "'s Turn";
    else
        playerBanner = "Player's Turn";

    std::cout << std::string(WIDTH, '-') << std::endl;
    std::cout << centerText(playerBanner, WIDTH) << std::endl;
    std::cout << std::string(WIDTH, '-') << std::endl;
}

// Bal Transfer Menus
void GameUI::displayBalanceTransferSender (vector<Player> vec) {
    
}
void GameUI::displayBalanceTransferReceiver(vector<Player> vec) {
    
}
void GameUI::displayBalanceTransferConfirmation(const Player& sender, const Player& receiver, int amount) {
    
}

void GameUI::displayEndScreen() {
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "                  GAME OVER" << endl;
    cout << endl;
    cout << endl;
    cout << endl;
}

