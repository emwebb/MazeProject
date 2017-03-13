#ifndef Game_hpp
#define Game_hpp

#include <string>
#include "Scene.hpp"

class Scene;

class Game {
public:
    virtual void switchScene(Scene* scene);
    virtual void startGame(Scene * startingScene);
    virtual bool setWindowSize(int width, int height);
    virtual void setWindowName(std::string name);
    virtual int getWidth();
    virtual int getHeight();
};

#endif /* Game_hpp */
