#ifndef ShaderProgram_hpp
#define ShaderProgram_hpp

#include "gl.h"
#include "logger.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <vector>

class ShaderProgram {
    GLuint program_id;
    GLuint vertex_id;
    GLuint fragment_id;
    
public:
    ShaderProgram(std::string vertex, std::string fragment, bool isFile);
    ShaderProgram();
    void use();
    GLuint getProgramID();
    GLint getUniformLocation(std::string uniform_name);
    GLint getAttributeLocation(std::string attribute_name);
    ~ShaderProgram();
};

#endif /* ShaderProgram_hpp */
