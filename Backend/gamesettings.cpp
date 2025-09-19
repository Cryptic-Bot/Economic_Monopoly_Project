#include "gamesettings.hpp"
// Accessor/Mutator functions for private values
void GameManager::setnPlayers(int n) { // Mutator
    nPlayers = n;
}
int GameManager::accessnPlayers() const { // Accessor
    return nPlayers;
}
void GameManager::setGlobalTurns(int n) { // Mutator
    globalTurns = n;
}
int GameManager::accessGlobalTurns() const { // Accessor
    return globalTurns;
}
void GameManager::setnPlayersGone(int n) { // Mutator
    nPlayersGone = n;
}
int GameManager::accessnPlayersGone() const { // Accessor
    return nPlayersGone;
}
vector<Player>& GameManager::modifyPlayersVec() {
    return players;
}
const vector<Player>& GameManager::accessPlayersVec() const {
    return players;
}
void GameManager::fillPlayersVec(vector<Player>& vec) {
    for (int i = 0; i < (int)vec.size(); i++) {
        players.push_back(vec[i]);
    }
}
bool GameManager::accessAllPlayersGone() const {
    return allPlayersGone;
}
void GameManager::setAllPlayersGone(bool& state) {
    allPlayersGone = state;
}
void GameManager::collectiveEconomy() {
    cout << endl;
    int nPlayrs = accessnPlayers(); // Create local variable for nPlayers
    
    // Clear leftover newline if coming from a cin >> call
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    int n = 0;
    for (int i = 0; i < nPlayrs; ++i) {
        ++n;
        cout << "Enter name for player #" << (i + 1) << ": ";
        string name;
        getline(cin, name);
        if (name == "Colin" || name == "colin") {
            name = "Bigfoot";
        }
        
        // Player constructor
        players.push_back(Player(n, name, 1500, Comrade()));
    }
}
//cout << "======= 2. Market Economy ============" << endl;
//cout << "     Players are randomly assigned preset jobs, each with distinct income levels. This mode models a competitive labor market where income varies based on occupation. "<< endl;
void GameManager::marketEconomy() {
    cout << endl;
    int nPlayrs = accessnPlayers(); // Create local variable for nPlayers
    // Clear leftover newline if coming from a cin >> call
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // Random setup
    random_device rd;
    mt19937 gen(rd());
    // Weighted list of job factories based on estimated US income distribution
    struct JobEntry {
        function<Job()> factory;
        int weight; // higher weight = more common
    };
    vector<JobEntry> jobPool = {
        { [](){ return FastFoodWorker(); }, 15 },
        { [](){ return Barista(); }, 14 },
        { [](){ return RetailWorker(); }, 14 },
        { [](){ return Waiter(); }, 13 },
        { [](){ return SocialWorker(); }, 12 },
        { [](){ return Artist(); }, 11 },
        { [](){ return Mechanic(); }, 10 },
        { [](){ return Teacher(); }, 10 },
        { [](){ return Chef(); }, 10 },
        { [](){ return Banker(); }, 9 },
        { [](){ return Nurse(); }, 8 },
        { [](){ return Electrician(); }, 7 },
        { [](){ return Lawyer(); }, 4 },
        { [](){ return Scientist(); }, 4 },
        { [](){ return SoftwareEngineer(); }, 3 },
        { [](){ return Doctor(); }, 2 },
        { [](){ return Entrepreneur(); }, 1 },
        { [](){ return Economist(); }, 5 },
        { [](){ return Hitman(); }, 2 },
        { [](){ return PoliceOfficer(); }, 5 },
        { [](){ return Accountant(); }, 6 },
        { [](){ return AIchatbot(); }, 3 },
        { [](){ return Alien(); }, 4 }
    };
    int n = 0;
    for (int i = 0; i < nPlayrs; ++i) {
        ++n;
        cout << "Enter name for player #" << (i + 1) << ": ";
        string name;
        getline(cin, name);
        if (name == "Colin" || name == "colin") {
            name = "Bigfoot";
        }
        // Random weighted selection
        int totalWeight = 0;
        for (auto &entry : jobPool) totalWeight += entry.weight;
        uniform_int_distribution<> dist(1, totalWeight);
        int rnd = dist(gen);
        Job chosenJob = jobPool.front().factory(); // default in case loop fails
        for (auto &entry : jobPool) {
            rnd -= entry.weight;
            if (rnd <= 0) {
                chosenJob = entry.factory();
                break;
            }
        }
        // Create and store player with chosen job
        players.push_back(Player(n, name, 1500, chosenJob));
    }
}
// Show all available jobs in a numbered list
void GameManager::displayAvailableJobs(const std::vector<Job>& jobs) {
    cout << "\n======= Available Jobs =======\n";
    int idx = 1;
    for (const auto &job : jobs) {
        cout << idx++ << ". " << job.name
            << " — $" << job.baseSalary
            << " — " << job.abilityName
            << " (" << job.description << ")\n";
    }
    cout << "==============================\n";
}
// Prompt a player to choose a job
Job GameManager::chooseJobMenu(std::vector<Job> &availableJobs) {
    while (true) {
        displayAvailableJobs(availableJobs);
        cout << "Enter the number of the job you want: ";
        int choice;
        if (cin >> choice) {
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear leftover chars
            if (choice >= 1 && choice <= static_cast<int>(availableJobs.size())) {
                // Store selection
                Job selectedJob = availableJobs[choice - 1];
                // Remove from available list so others can't pick it
                availableJobs.erase(availableJobs.begin() + (choice - 1));
                return selectedJob;
            }
        } else {
            cin.clear(); // reset failbit in case of bad input
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        cout << "Invalid selection. Please try again.\n";
    }
}
//cout << "======= 3. Meritocracy Choice ========" << endl;
//cout << "     Players freely select their jobs from a preset list, balancing income potential against abilities. This mode reflects a society where personal skill and career decisions directly influence earnings." << endl;
void GameManager::meritocracyChoice() {
    cout << endl;
    int nPlayrs = accessnPlayers();
    
    // Clear leftover newline from any cin >> before
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    // Build initial list of available jobs (unique instances)
    vector<Job> availableJobs = {
        FastFoodWorker(), Barista(), RetailWorker(), Waiter(),
        SocialWorker(), Artist(), Mechanic(), Teacher(), Chef(),
        Banker(), Nurse(), Electrician(), Lawyer(), Scientist(),
        SoftwareEngineer(), Doctor(), Entrepreneur(), Comrade(),
        Economist(), Hitman(), PoliceOfficer(), Accountant(),
        AIchatbot(), Alien()
    };
    
    int playerNum = 0;
    for (int i = 0; i < nPlayrs; ++i) {
        playerNum++;
        cout << "Enter name for player #" << playerNum << ": ";
        string name;
        getline(cin, name);
        if (name == "Colin" || name == "colin") {
            name = "Bigfoot";
        }
        
        // Player chooses job from menu
        Job chosenJob = chooseJobMenu(availableJobs);
        
        // Add player with chosen job
        players.push_back(Player(playerNum, name, 1500, chosenJob));
        
        cout << name << " chose job: " << chosenJob.name
            << " ($" << chosenJob.baseSalary << ")\n\n";
    }
}
void GameManager::incomeVolatility() {
    cout << endl;
    int nPlayrs = accessnPlayers(); // Create local variable for nPlayers
    
    // Clear leftover newline if coming from a cin >> call
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    int n = 0;
    for (int i = 0; i < nPlayrs; ++i) {
        ++n;
        cout << "Enter name for player #" << (i + 1) << ": ";
        string name;
        getline(cin, name);
        if (name == "Colin" || name == "colin") {
            name = "Bigfoot";
        }
        
        players.push_back(Player(n, name, 1500, Freelancer()));
    }
}
int MenuFunction::jobsMenu(GameManager& game) {
    GameUI graphics;
    
    bool areYouSure = false;
    
    do {
        graphics.displayJobMenu();       // Show menu once each loop
        char userinput;
        cin >> userinput;
        
        if (userinput == '1') {
            game.collectiveEconomy();
            return 1;
        } else if (userinput == '2') {
            game.marketEconomy();
            return 1;
        } else if (userinput == '3') {
            game.meritocracyChoice();
            return 1;
        } else if (userinput == '4') {
            game.incomeVolatility();
            return 1;
        } else if (userinput == 'I' || userinput == 'i') {
            graphics.displayJobInfoMenu();
        } else if (userinput == 'Q' || userinput == 'q') {
            char ui2;
            cout << "Are you sure you want to quit the game? Enter Q again to quit or any other key to continue: ";
            cin >> ui2;
            if (ui2 == 'Q' || ui2 == 'q') {
                areYouSure = true;
            }
        } else {
            cout << "Invalid response. Try again.\n" << endl;
            graphics.displayJobMenu();
        }
    } while (areYouSure == false);
    cout << endl;
    return 0;
}
int GameManager::setup() {
    // Setup
    MenuFunction menu;
    cout << "Ready to start? Time for game setup!";
    string dummy; // what do this do?? I kinda forgot but I don't want to remove it (JENGA)
    getline(cin, dummy);
    cout << endl;
    
    // Number of players
    do {
        cout << "How many players?: ";
        cin >> nPlayers;
        if (nPlayers <= 1 || nPlayers >= 8) { cout << "Sorry, we don't support that number of players. Try again." << endl; }
    } while (nPlayers <= 1 || nPlayers >= 8);
    cout << endl;
    
    if (menu.jobsMenu(*this) == 0) { return 0; }
    
    // Player confirmation screen
    else {
        cout << "\n ----- Players created -----\n";
        vector<Player> vec = accessPlayersVec();
        for (auto &player : vec) {
            player.displayStartingStatus();
            cout << endl;
        }
    }
    return 1;
}
// RN it just loops through the menu repeatedly
// Need to be able to cycle through and keep track of turns
// Meaning update things
// Need
// 1. Function to print Turn
// 2. Function to print player
// 3. Update player/turn count
// 4. Skip players if out (later)
// 5. Use special menus for certain player statuses
void MenuFunction::mainMenu(GameManager& game) {
    GameUI graphics;
    MenuFunction menu;
    char userinput;
    bool areYouSure = false;
    graphics.displayGlobalTurn(game);
    graphics.displayPlayerTurn(game, game.accessPlayersVec());
    
    
    do {
        cout << endl;
        graphics.displayMenu();
        cin >> userinput;
        
        if (userinput == 'E' || userinput == 'e') {  // End Player turn
            // === COUNT ACTIVE PLAYERS ===
            int activePlayers = 0;
            int winnerIndex = -1;
            const auto& allPlayers = game.accessPlayersVec();
            for (int i = 0; i < (int)allPlayers.size(); i++) {
                if (!allPlayers[i].getInsolventBankrupt()) {
                    activePlayers++;
                    winnerIndex = i;
                }
            }
            // === END GAME IF ONLY ONE PLAYER LEFT ===
            if (activePlayers <= 1) {
                if (winnerIndex != -1) {
                    cout << "\nGame Over! Winner is: "
                        << allPlayers[winnerIndex].getName() << " 🎉" << endl;
                } else {
                    cout << "\nGame Over! No winners. Everyone is bankrupt!" << endl;
                }
                graphics.displayEndScreen();
                return;
            }
            // === MOVE TO NEXT PLAYER ===
            game.setnPlayersGone(game.accessnPlayersGone() + 1);
            bool foundAcceptablePlayer = false;
            int attempts = 0;
            bool turnAdvanced = false; // track if global turn changes
            int totalPlayers = game.accessnPlayers();
            while (!foundAcceptablePlayer && attempts < totalPlayers) {
                // Wrap if end of player list
                if (game.accessnPlayersGone() >= totalPlayers) {
                    game.setnPlayersGone(0);
                    game.setGlobalTurns(game.accessGlobalTurns() + 1);
                    turnAdvanced = true; // we actually advanced to a new global turn
                }
                // Skip bankrupt players
                if (allPlayers[game.accessnPlayersGone()].getInsolventBankrupt()) {
                    game.setnPlayersGone(game.accessnPlayersGone() + 1);
                } else {
                    foundAcceptablePlayer = true;
                }
                attempts++;
            }
            // === ONLY SHOW GLOBAL TURN IF IT CHANGED AND GAME IS STILL RUNNING ===
            if (turnAdvanced) {
                graphics.displayGlobalTurn(game);
            }
            // Always show current player's turn
            graphics.displayPlayerTurn(game, game.accessPlayersVec());
        } else if (userinput == '1') {      // 1. View info - need to do
            graphics.displayViewInfo();
            menu.viewInfoMenu(game);
        } else if (userinput == '2') {      // 2. Report updates - need to do
            graphics.displayReportUpdates();
            menu.reportUpdatesMenu(game);
        } else if (userinput == '3') {      // 3. Balance Transfer - Done yay
            menu.balanceTransferMenu(game);
        } else if (userinput == '4') {      // 4. Loans - need to do
            graphics.displayLoans();
            menu.loansMenu(game);
        } else if (userinput == '5') {      // 5. Player to Player Relations - later problem
            graphics.displayP2Prelations();
            menu.P2PrelationsMenu(game);
        } else if (userinput == 'Q' || userinput == 'q') {
            char ui2;
            cout << "Are you sure you want to quit the game? Enter Q again to quit or any other key to continue: ";
            cin >> ui2;
            if (ui2 == 'Q' || ui2 == 'q') {
                areYouSure = true;
            }
        } else {                           // Invalid input case
            cout << "Invalid choice." << endl;
            continue;
        }
        cout << endl;
        
    } while (areYouSure == false);
}
#include "gamesettings.hpp"
#include <limits>
// Select sender (returns -1 exit, -2 outside source)
int GameManager::selectSender(GameUI& ui) {
    while (true) {
        ui.displayBalanceTransferSender(players);
        string input;
        cin >> input;
        if (input == "E" || input == "e") return -1; // Exit
        if (input == "S" || input == "s") return -2; // Outside source
        try {
            int choice = stoi(input);
            if (choice >= 1 && choice <= (int)players.size()) {
                return choice - 1;
            }
        } catch (...) {}
        cout << "Invalid selection. Please try again.\n";
    }
}
// Select receiver (returns -1 exit, -2 outside source)
int GameManager::selectReceiver(GameUI& ui, int senderIndex) {
    while (true) {
        ui.displayBalanceTransferReceiver(players);
        string input;
        cin >> input;
        if (input == "E" || input == "e") return -1;
        if (input == "S" || input == "s") return -2;
        try {
            int choice = stoi(input);
            if (choice >= 1 && choice <= (int)players.size()) {
                if (choice - 1 == senderIndex) {
                    cout << "Receiver cannot be the same as sender.\n";
                    continue;
                }
                return choice - 1;
            }
        } catch (...) {}
        cout << "Invalid selection. Please try again.\n";
    }
}
// Ask for transfer amount
int GameManager::requestTransferAmount() {
    cout << "Enter transfer amount: ";
    int amount;
    cin >> amount;
    if (cin.fail() || amount <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid amount.\n";
        return -1;
    }
    return amount;
}
// Confirm and execute transfer
bool GameManager::confirmTransfer(GameUI& ui, int senderIndex, int receiverIndex, int amount) {
    // Temporary sender/receiver display
    if (senderIndex != -2 && (senderIndex < 0 || senderIndex >= (int)players.size())) return false;
    if (receiverIndex != -2 && (receiverIndex < 0 || receiverIndex >= (int)players.size())) return false;
    if (senderIndex != -2 && !players[senderIndex].hasEnoughCash(amount)) {
        cout << "Error: Sender does not have enough funds.\n";
        return false;
    }
    
    // Show confirmation
    if (senderIndex >= 0)
        ui.displayBalanceTransferConfirmation(players[senderIndex],
                                             (receiverIndex >= 0 ? players[receiverIndex] : Player(0, "Outside Source", 0, Comrade())),
                                             amount);
    else
        ui.displayBalanceTransferConfirmation(Player(0, "Outside Source", 0, Comrade()),
                                             (receiverIndex >= 0 ? players[receiverIndex] : Player(0, "Outside Source", 0, Comrade())),
                                             amount);
    char confirm;
    cin >> confirm;
    if (confirm != 'Y' && confirm != 'y') {
        cout << "Transfer cancelled.\n";
        return false;
    }
    // Adjust balances
    if (senderIndex != -2) players[senderIndex].addCash(-amount);
    if (receiverIndex != -2) players[receiverIndex].addCash(amount);
    cout << "Transfer successful!\n";
    
    cout << endl;
    cout << "New Balances: " << endl;
    cout << players[senderIndex].getName() << ": " << players[senderIndex].getCash() << endl;
    cout << players[receiverIndex].getName() << ": " <<  players[receiverIndex].getCash();
    
    
    return true;
}
// Main transfer workflow
void GameManager::balanceTransferMenu(GameUI& ui) {
    int senderIndex = selectSender(ui);
    if (senderIndex == -1) return;
    int receiverIndex = selectReceiver(ui, senderIndex);
    if (receiverIndex == -1) return;
    int amount = requestTransferAmount();
    if (amount <= 0) return;
    confirmTransfer(ui, senderIndex, receiverIndex, amount);
}
void MenuFunction::balanceTransferMenu(GameManager& game) {
    GameUI ui;
    game.balanceTransferMenu(ui);
}
void MenuFunction::viewInfoMenu(GameManager& game) {
    
}
void MenuFunction::reportUpdatesMenu(GameManager& game) {
    
}
void MenuFunction::loansMenu(GameManager& game) {
    
}
void MenuFunction::P2PrelationsMenu(GameManager& game) {
    
}
