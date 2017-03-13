#include "Scene.hpp"

#include "gl.h"
#include <iostream>

Scene::Scene(Game* game) {
    this->game = game;
}

void Scene::StartScene() {
    std::cout << "Default scene started" << std::endl;
    glClearColor(1, 0, 0, 0);
    
    
}

void Scene::OnRenderUpdate(float deltaTime){
    // This is the defuault scene so it won't actually do anything.
    glClear(GL_COLOR_BUFFER_BIT);
    std::clog << "Render called" << std::endl;
    std::clog << "Delta time = " << deltaTime << std::endl;
    std::clog << "FPS = " << 1.0f/deltaTime << std::endl;
}

bool Scene::allowQuit() {
    return true;
}

void Scene::OnScreenResize(int width, int height){
    // DO NOTHING
}
void Scene::OnKeyDown(std::string key) {
    
}
void Scene::OnKeyUp(std::string key) {
    
}
