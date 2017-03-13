#include "matrix44.hpp"

Matrix44::Matrix44(float data[16]){
    for (int n = 0; n < 16; n++) {
        this->data[n] = data[n];
    }
}

Matrix44 Matrix44::operator+(const Matrix44& other){
    float newData[16];
    for (int n = 0; n < 16; n++) {
        newData[n] = data[n] + other.data[n];
    }
    
    return Matrix44(newData);
}

float Matrix44::get(int x, int y){
    return data[(x * 4)+y];
}

Matrix44 Matrix44::operator*(const Matrix44& other){
    float newData[16];
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            newData[(x * 4)+y] = 0.0f;
            for (int n = 0; n < 4; n++) {
                newData[(x * 4)+y] += data[(x * 4)+n] * other.data[(n * 4)+y];
            }
        }
    }
    
    return Matrix44(newData);
}

float* Matrix44::getData() {
    return data;
}


Matrix44 getIdentityMatrix() {
    float data[16] = {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1};
    return Matrix44(data);
}
Matrix44 getTranslationMatrix(float x, float y, float z){
    float data[16] = {
        1,0,0,x,
        0,1,0,y,
        0,0,1,z,
        0,0,0,1};
    return Matrix44(data);
}
Matrix44 getScaleMatrix(float x, float y, float z){
    float data[16] = {
        x,0,0,0,
        0,y,0,0,
        0,0,z,0,
        0,0,0,1};
    return Matrix44(data);
}
Matrix44 getXRotationMatrix(float radians){
    float data[16] = {
        1,0            ,0             ,0,
        0,static_cast<float>(cos(radians)),static_cast<float>(-sin(radians)),0,
        0,static_cast<float>(sin(radians)),static_cast<float>(cos(radians)) ,0,
        0,0            ,0             ,1};
    return Matrix44(data);
}


Matrix44 getYRotationMatrix(float radians){
    float data[16] = {
        static_cast<float>(cos(radians)) ,0,static_cast<float>(sin(radians)),0,
        0             ,1,0            ,0,
        static_cast<float>(-sin(radians)),0,static_cast<float>(cos(radians)),0,
        0             ,0,0            ,1};
    return Matrix44(data);
}
Matrix44 getZRotationMatrix(float radians){
    float data[16] = {
        static_cast<float>(cos(radians)),static_cast<float>(-sin(radians)),0,0,
        static_cast<float>(sin(radians)),static_cast<float>(cos(radians)) ,0,0,
        0            ,0             ,1,0,
        0            ,0             ,0,1};
    return Matrix44(data);
}


Matrix44 getXYZRotationMatrix(float xRadians,float yRadians,float zRadians){
    return getXRotationMatrix(xRadians) * getYRotationMatrix(yRadians) * getZRotationMatrix(zRadians);
}

Matrix44 getPerspectiveMatrix(float aspectRatio,float zNear,float zFar,float fov){
    
    float a = 1.0f/tanf(fov/2.0f);
    float data[16] = {
        a/aspectRatio                    ,0                     ,0                              ,0                           ,
        0                                ,a                     ,0                              ,0                           ,
        0                                ,0                     ,(-zNear-zFar)/(zFar-zNear)     ,-(2.0f*zFar*zNear)/(zFar-zNear),
        0                                ,0                     ,-1.0f                          ,0                          };
    
    return Matrix44(data);

}

Matrix44 getViewMatrix(float x, float y, float z, float rx, float ry, float rz) {
    return getXYZRotationMatrix(rx, ry, rz) * getTranslationMatrix(x, y, z);
}
