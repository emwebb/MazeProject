//
//  Camera.hpp
//  MazeProject
//
//  Created by Ethan Webb on 10/03/2017.
//  Copyright © 2017 Ethan. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include "matrix44.hpp"
#include "logger.hpp"
#include <string>
#include <math.h>
class Camera {
    float x,y,z,rx,ry,rz;
    bool allowedUpsideDown;
    public :
    Camera();
    Matrix44 getViewMatrixFromCamera();
    void move(float x,float y,float z);
    void moveLocal(float x,float y,float z);
    void rotate(float x, float y, float z);
    void setAllowUpsideDown(bool allow);
    void setPosistion(float x, float y, float z);
    void setRotation(float x, float y, float z);
};

#endif /* Camera_hpp */
