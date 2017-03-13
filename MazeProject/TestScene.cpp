#include "TestScene.hpp"

float triangle_array[96] = {
    // XYZ RGB
     1, 1, 1, 0, 0, 1,
    -1, 1, 1, 0, 1, 0,
     1,-1, 1, 1, 1, 0,
    -1,-1, 1, 1, 0, 0,
    
    
     1, 1,-1, 1, 0 , 0,
     1,-1,-1, 0, 1 , 0,
    -1, 1,-1, 1, 1 , 0,
    -1,-1,-1, 0, 0 , 1,
    
    -1, 1, 1, 0, 0, 1,
    -1, 1,-1, 1, 1, 0,
    -1,-1, 1, 0, 1, 0,
    -1,-1,-1, 1, 0, 0,
    
    
     1, 1, 1, 0, 0, 1,
     1,-1, 1, 0, 1, 0,
     1, 1,-1, 1, 1, 0,
     1,-1,-1, 1, 0, 0,
    
};


TestScene::TestScene(Game* game) : Scene(game) {
    
}

void TestScene::StartScene(){
    //Create the VBO for the triangle
    triangle = new VBO<float>(GL_ARRAY_BUFFER,triangle_array,96,GL_STATIC_DRAW);
    
    //Create the shader program.
    colourShader = new ShaderProgram("colour.vert", "colour.frag",true);
    colourShader->use();
    //Tell the VBO where to put what data.
    triangle->insertVertexAttributeFormat("pos", 3, false, 6,0);
    triangle->insertVertexAttributeFormat("col", 3, false, 6,3);
    //When ever we clear the colour buffer set the screen to red.
    glClearColor(0, 0, 0, 0);
    game->setWindowName("Maze Game!");
    
    //Make sure the view port is set up correctly.
    glViewport(0, 0, game->getWidth(), game->getHeight());
    
    keys_pressed.forward = false;
    keys_pressed.backward = false;
    keys_pressed.sleft = false;
    keys_pressed.sright = false;
    keys_pressed.rleft = false;
    keys_pressed.rright = false;
}


void TestScene::OnRenderUpdate(float deltaTime){
    
    
    
    //Game logic update
    
    if(keys_pressed.forward) {
        camera.moveLocal(0, 0, playerMoveSpeed * deltaTime);
        logi("TestScene", "Moved forward!");
    }
    if(keys_pressed.backward) {
        camera.moveLocal(0, 0, -playerMoveSpeed * deltaTime);
        logi("TestScene", "Moved backwards!");
    }
    if(keys_pressed.sright) {
        camera.moveLocal(-playerMoveSpeed * deltaTime, 0,0);
    }
    if(keys_pressed.sleft) {
        camera.moveLocal(playerMoveSpeed * deltaTime, 0,0);
    }
    if(keys_pressed.rright) {
        camera.rotate(0, playerMoveSpeed * deltaTime, 0);
        logi("TestScene", "Rotate right!");
    }
    if(keys_pressed.rleft) {
        camera.rotate(0, -playerMoveSpeed * deltaTime, 0);
    }
    
    glEnable (GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen.
    colourShader->use(); // Tell the colour shader we want to use it.
    triangle->bind(colourShader); // Bind the data from the VBO.
    // Create the model matrix
    float ar = (float)game->getWidth()/(float)game->getHeight();
    Matrix44 transMatrix = getTranslationMatrix(0, 0, 0);
    Matrix44 rotMatrix = getYRotationMatrix(0);
    Matrix44 modelMatrix = transMatrix * rotMatrix;
    Matrix44 viewMatrix = camera.getViewMatrixFromCamera();
    Matrix44 perspectiveMatrix = getPerspectiveMatrix(ar, 0.001f, 100.0f, 90.0f*M_PI/180.0F);
    Matrix44 mat = perspectiveMatrix * viewMatrix * modelMatrix;
    
    // Bind the model matrix
    glUniformMatrix4fv(colourShader->getUniformLocation("trans"), 1, true, mat.getData());
    // DRAW!
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);
    glDrawArrays(GL_TRIANGLE_STRIP, 8, 4);
    glDrawArrays(GL_TRIANGLE_STRIP, 12, 4);
    //Unbind everything!
    triangle->unbind(colourShader);
    glUseProgram(0);
    glDisable (GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

}

bool TestScene::allowQuit(){
    return true;
}


void TestScene::OnScreenResize(int width, int height) {
    
    //Make sure the view port is set up correctly.
    glViewport(0, 0, width, height);
}

void TestScene::OnKeyDown(std::string key){
    logi("TestScene", "Key pressed : " + key);
    if(key == "W") {
        keys_pressed.forward = true;
    } else if(key == "S") {
        keys_pressed.backward = true;
    } else if(key == "A") {
        keys_pressed.sleft = true;
    } else if(key == "D") {
        keys_pressed.sright = true;
    } else if(key == "Q") {
        keys_pressed.rleft = true;
    } else if(key == "E") {
        keys_pressed.rright = true;
    }
}

void TestScene::OnKeyUp(std::string key){
    logi("TestScene", "Key released : " + key);
    if(key == "W") {
        keys_pressed.forward = false;
    } else if(key == "S") {
        keys_pressed.backward = false;
    } else if(key == "A") {
        keys_pressed.sleft = false;
    } else if(key == "D") {
        keys_pressed.sright = false;
    } else if(key == "Q") {
        keys_pressed.rleft = false;
    } else if(key == "E") {
        keys_pressed.rright = false;
    }
}

TestScene::~TestScene(){
    delete triangle;
    delete colourShader;
}

