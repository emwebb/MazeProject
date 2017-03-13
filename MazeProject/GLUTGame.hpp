#ifndef GLUTGame_hpp
#define GLUTGame_hpp

#include <exception>

#ifdef __linux__
#include <GL/freeglut.h>
#elif __APPLE__
#include <GLUT/GLUT.h>
#endif
#include <string>

#include "Game.hpp"
#include "logger.hpp"


class GLUTGame : public Game {
private :
    int windowID;
    bool gameRunning;
    
    int lastUpdateTime;
    
    Scene* currentScene;
    Scene* newScene;

protected :
    
    static void staticDisplayFunction();
    void displayFunction();
    
public:
    GLUTGame(int argc, char** argv);
    void switchScene(Scene* scene);
    void startGame(Scene * startingScene);
    bool setWindowSize(int width, int height);
    void setWindowName(std::string name);
    int getWidth();
    int getHeight();
    ~GLUTGame();
};

#endif /* GLUTGame_hpp */
