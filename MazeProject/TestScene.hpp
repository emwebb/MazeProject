#ifndef TestScene_hpp
#define TestScene_hpp

#include "Scene.hpp"
#include "ShaderProgram.hpp"
#include "VBO.hpp"
#include "gl.h"
#include "matrix44.hpp"
#include "Camera.hpp"
#include <string>
#include <cmath>

struct KeysPressed {
    bool forward;
    bool backward;
    bool sleft;
    bool sright;
    bool rleft;
    bool rright;
};

class TestScene : public Scene {
    VBO<float> *triangle;
    ShaderProgram *colourShader;
    Camera camera;
    struct KeysPressed keys_pressed;
    float playerMoveSpeed = 3.0f;
    
public:
    TestScene(Game* game);
    void StartScene();
    void OnRenderUpdate(float deltaTime);
    bool allowQuit();
    void OnScreenResize(int width, int height);
    void OnKeyDown(std::string key);
    void OnKeyUp(std::string key);
    ~TestScene();
};

#endif /* TestScene_hpp */
