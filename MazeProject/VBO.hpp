#ifndef VBO_hpp
#define VBO_hpp

#include "gl.h"
#include "ShaderProgram.hpp"
#include "logger.hpp"
#include <vector>
#include <string>
#include <map>
#include <iostream>


struct vertex_format {
    GLuint size;
    bool normalized;
    GLsizei stride;
    int offset;
};

typedef struct vertex_format vertex_format;

template<typename T> class VBO {
    GLenum type, target;
    GLuint id;
    std::map<std::string,vertex_format> vertex_formats;
    
public:
    VBO(GLenum target, T* data, int size,GLenum usage);
    VBO(GLenum target, std::vector<T> data,GLenum usage);
    VBO();
    void insertVertexAttributeFormat(std::string variable_name,GLuint size,bool normalized,GLsizei stride,int offset);
    void bind(ShaderProgram *program);
    void unbind(ShaderProgram *program);
    ~VBO();
};
#endif /* VBO_hpp */
