#include "GLUTGame.hpp"

static GLUTGame* currentGame;


GLUTGame::GLUTGame(int argc, char** argv) {
    // Set up everything for the game.
    if(currentGame) {
        loge("GLUTGame", "Attempted to create a second GLUTGame");
        throw std::logic_error("There may only be 1 GLUTGame at any one time!");
    }
    gameRunning = false;
    currentGame = this;
    newScene = NULL;
    currentScene = NULL;
    logi("GLUTGame","Initializing GLUT");
    glutInit(&argc, argv);
    
}
// Function to allow interaction between C and C++ for glut display function.
void GLUTGame::staticDisplayFunction(){
    if(currentGame) {
        currentGame->displayFunction();
    }
    
}

void GLUTGame::startGame(Scene* scene) {
    // Initiate the Window
    windowID = glutCreateWindow("GLUTGame");
    glutDisplayFunc(staticDisplayFunction);
    glutIdleFunc(staticDisplayFunction);
    gameRunning = true;
    newScene = scene;
    lastUpdateTime = glutGet(GLUT_ELAPSED_TIME);
    glutMainLoop();
}

void GLUTGame::switchScene(Scene *scene) {
    newScene = scene; // Next display cycle this will be set to the current scene and started.
}


void GLUTGame::displayFunction() {
    if(newScene) {
        // Switch to the new Scene!
        logi("GLUTGame","Switching to scene of type \"" + std::string(typeid(*newScene).name()) + "\"");
        delete currentScene;
        currentScene = newScene;
        newScene = NULL;
        currentScene->StartScene();
    }
    // Used for calculating Delta Time.
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    
    
    currentScene->OnRenderUpdate((float)(currentTime - lastUpdateTime)/1000.0f);
    lastUpdateTime = currentTime;
    glutSwapBuffers(); // Swap the buffer so it is displayed on the window.
}


bool GLUTGame::setWindowSize(int width, int height) {
    glutReshapeWindow(width, height);
    return true;
}

void GLUTGame::setWindowName(std::string name){
    glutSetWindowTitle(name.c_str());
}

int GLUTGame::getWidth() {
    return glutGet(GLUT_WINDOW_WIDTH);
}

int GLUTGame::getHeight() {
    return glutGet(GLUT_WINDOW_HEIGHT);
}

GLUTGame::~GLUTGame() {
    glutDestroyWindow(windowID);
    
    currentGame = NULL;
}
