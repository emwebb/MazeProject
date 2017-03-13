#ifndef SDL2Game_hpp
#define SDL2Game_hpp

#include "Game.hpp"
#include "logger.hpp"
#include <SDL2/SDL.h>

class SDL2Game : public Game {
private :
    SDL_Window* window;
    SDL_Renderer* render;
    bool gameRunning;
    
    int lastUpdateTime;
    
    Scene* currentScene;
    Scene* newScene;
    
protected :
    
    static void staticDisplayFunction();
    void displayFunction();
    
public:
    SDL2Game();
    void switchScene(Scene* scene);
    void startGame(Scene * startingScene);
    bool setWindowSize(int width, int height);
    void setWindowName(std::string name);
    int getWidth();
    int getHeight();
    ~SDL2Game();
};

#endif /* SDL2Game_hpp */
