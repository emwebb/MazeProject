#ifndef Scene_hpp
#define Scene_hpp

#include "Game.hpp"

class Game;

class Scene {
protected :
    Game* game;
public:
    Scene(Game* game);
    virtual void StartScene();
    virtual void OnRenderUpdate(float deltaTime);
    virtual bool allowQuit();
    virtual void OnScreenResize(int width, int height);
    virtual void OnKeyDown(std::string key);
    virtual void OnKeyUp(std::string key);
};

#endif /* Scene_hpp */
