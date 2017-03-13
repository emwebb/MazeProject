#ifndef matrix44_hpp
#define matrix44_hpp

#include <math.h>

class Matrix44 {
    
    float data[16];
    public:
    
    Matrix44(float[16]);
    Matrix44 operator+(const Matrix44& other);
    Matrix44 operator*(const Matrix44& other);
    float get(int x, int y);
    float* getData();
};

Matrix44 getIdentityMatrix();
Matrix44 getTranslationMatrix(float x, float y, float z);
Matrix44 getScaleMatrix(float x, float y, float z);
Matrix44 getXRotationMatrix(float radians);
Matrix44 getYRotationMatrix(float radians);
Matrix44 getZRotationMatrix(float radians);
Matrix44 getXYZRotationMatrix(float xRadians,float yRadians,float zRadians);
Matrix44 getPerspectiveMatrix(float aspectRatio,float zNear,float zFar,float fov);
Matrix44 getViewMatrix(float x, float y, float z, float rx, float ry, float rz);

#endif /* matrix44_hpp */
