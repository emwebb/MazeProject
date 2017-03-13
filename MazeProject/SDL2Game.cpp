#include "SDL2Game.hpp"

SDL2Game::SDL2Game() {
    //Set up SDL
    SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0");
    SDL_Init(SDL_INIT_VIDEO);
    gameRunning = false;
    newScene = NULL;
    currentScene = NULL;
}

void SDL2Game::startGame(Scene *startingScene){
    newScene = startingScene;
    // Initialise the Window
    SDL_CreateWindowAndRenderer(300, 300, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI , &window, &render);
    // Initialise OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetSwapInterval(1);
    lastUpdateTime = SDL_GetTicks();
    bool quit = false;
    while (!quit) {
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT : quit = currentScene->allowQuit(); break;
                case SDL_WINDOWEVENT :
                    switch (event.window.event) {
                        case SDL_WINDOWEVENT_RESIZED :
                            int width,height;
                            SDL_GL_GetDrawableSize(window, &width, &height);
                            currentScene->OnScreenResize(width, height);
                            break;
                    } break;
                case SDL_KEYDOWN :  currentScene->OnKeyDown(std::string(SDL_GetScancodeName(event.key.keysym.scancode))); break;
                case SDL_KEYUP :  currentScene->OnKeyUp(std::string(SDL_GetScancodeName(event.key.keysym.scancode))); break;
                    
                    
            }
        }
        if(newScene) {
            // Switch scene if the scene has changed
            logi("SDL2Renderer","Switching to scene of type \"" + std::string(typeid(*newScene).name()) + "\"");
            delete currentScene;
            currentScene = newScene;
            newScene = NULL;
            currentScene->StartScene();
        }
        int currentTime = SDL_GetTicks();
        
        
        currentScene->OnRenderUpdate((float)(currentTime - lastUpdateTime)/1000.0f);
        lastUpdateTime = currentTime;
        SDL_GL_SwapWindow(window);
    }
    
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    
    delete currentScene;
    if(newScene) {
        delete newScene;
    }
    
}

void SDL2Game::switchScene(Scene *scene) {
    newScene = scene;
}

int SDL2Game::getHeight(){
    int height = 0;
    SDL_GL_GetDrawableSize(window, NULL, &height);
    return height;
}

int SDL2Game::getWidth(){
    int width = 0;
    SDL_GL_GetDrawableSize(window, &width, NULL);
    return width;
}

bool SDL2Game::setWindowSize(int width, int height){
    SDL_SetWindowSize(window, width, height);
    return true;
}
void SDL2Game::setWindowName(std::string name){
    SDL_SetWindowTitle(window, name.c_str());
}
SDL2Game::~SDL2Game() {
    
}
