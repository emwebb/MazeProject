#include "main.hpp"
int main(int argc, char ** argv) {
    init_log(); // Get the logger running
    logi("main", "Starting game");
    Game* game = new SDL2Game(); // Create the game!
    game->startGame(new TestScene(game)); // Start the game!
    
    delete game;
    return 0;
}
