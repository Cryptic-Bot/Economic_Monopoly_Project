
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


// Implementation Notes:
// - turn based
// - income for passing go
// - random event timer


