//
//  Camera.cpp
//  MazeProject
//
//  Created by Ethan Webb on 10/03/2017.
//  Copyright © 2017 Ethan. All rights reserved.
//

#include "Camera.hpp"


Camera::Camera() {
    x = 0;
    y = 0;
    z = 0;
    rx = 0;
    ry = 0;
    rz = 0;
    allowedUpsideDown = false;
}

Matrix44 Camera::getViewMatrixFromCamera(){
    return getViewMatrix(x,y,z,rx,ry,rz);
}
void Camera::move(float x,float y,float z){
    this->x += x;
    this->y += y;
    this->z += z;
}

void Camera::moveLocal(float dx,float dy,float dz){
    this->x += dz * -sinf(ry) + dx * cosf(ry);
    this->y += dy;
    this->z += dz * cosf(ry) + dx * sinf(ry);
    
    logi("Camera","Pos :" + std::to_string(this->x) + ","+ std::to_string(this->y) + ","+ std::to_string(this->z));
}

void Camera::rotate(float x, float y, float z){
    this->rx += x;
    this->ry += y;
    this->rz += z;
}
void Camera::setAllowUpsideDown(bool allow){
    allowedUpsideDown = allow;
}
void Camera::setPosistion(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}
void Camera::setRotation(float x, float y, float z){
    this->rx = x;
    this->ry = y;
    this->rz = z;
}
