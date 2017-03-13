#include "ShaderProgram.hpp"

ShaderProgram::ShaderProgram() {
    
}

ShaderProgram::ShaderProgram(std::string vertex, std::string fragment, bool isFile) {
    
    std::string vertex_glsl;
    std::string fragment_glsl;
    // If we were given the URL rather than actual program then get the data from the file.
    if(isFile){
        std::ifstream vertex_file(vertex);
        vertex_glsl.assign((std::istreambuf_iterator<char>(vertex_file)), (std::istreambuf_iterator<char>()));
        std::ifstream fragment_file(fragment);
        fragment_glsl.assign((std::istreambuf_iterator<char>(fragment_file)), (std::istreambuf_iterator<char>()));
    } else {
        vertex_glsl.assign(vertex);
        fragment_glsl.assign(fragment);
    }
    GLint success;
    
    GLint log_length;
    
    GLchar* log;
    
    vertex_id = glCreateShader(GL_VERTEX_SHADER); //Create the shader
    const char* cVertex = vertex_glsl.c_str();
    glShaderSource(vertex_id, 1, &cVertex, NULL); //Upload the shader program.
    glCompileShader(vertex_id); // Compile the shader.
    
    // Make sure the shader compiled.
    glGetShaderiv(vertex_id, GL_COMPILE_STATUS, &success);
    if(success == GL_FALSE) {
        loge("ShaderProgram","Failed to compile vertex shader!");
    }
    // Get the log of the shader compile and log it.
    glGetShaderiv(vertex_id, GL_INFO_LOG_LENGTH, &log_length);
    log = new GLchar[log_length + 1];
    glGetShaderInfoLog(vertex_id, log_length, &log_length, log);
    logi("ShaderProgram" , "Vertex Shader Log :");
    logi("ShaderProgram", std::string(log));
    delete [] log;
    
    
    
    fragment_id = glCreateShader(GL_FRAGMENT_SHADER); // Create the shader
    const char* cFragment = fragment_glsl.c_str();
    glShaderSource(fragment_id, 1, &cFragment, NULL); //Upload the shader program.
    glCompileShader(fragment_id); // Compile the shader
    
    // Make sure the shader compiled
    glGetShaderiv(fragment_id, GL_COMPILE_STATUS, &success);
    if(success == GL_FALSE) {
        loge("ShaderProgram","Failed to compile fragment shader!");
    }
    
    // Get the log of the shader compile and log it.
    glGetShaderiv(fragment_id, GL_INFO_LOG_LENGTH, &log_length);
    log = new GLchar[log_length + 1];
    glGetShaderInfoLog(fragment_id, log_length, &log_length, log);
    logi("ShaderProgram" , "Fragment Shader Log :");
    logi("ShaderProgram", std::string(log));
    delete [] log;
    
    program_id = glCreateProgram();
    
    // Attach the shaders to the program and link it.
    glAttachShader(program_id, vertex_id);
    glAttachShader(program_id, fragment_id);
    glLinkProgram(program_id);
    
    
    // Make sure the program linked.
    glGetProgramiv(program_id,GL_LINK_STATUS,&success);
    
    if(success == GL_FALSE) {
        loge("ShaderProgram","Failed to link program!");
    }
}

void ShaderProgram::use(){
    glUseProgram(program_id);
}

GLuint ShaderProgram::getProgramID() {
    return program_id;
}

GLint ShaderProgram::getUniformLocation(std::string uniform_name){
    return glGetUniformLocation(program_id, uniform_name.c_str());
}

GLint ShaderProgram::getAttributeLocation(std::string attribute_name){
    return glGetAttribLocation(program_id, attribute_name.c_str());
}

ShaderProgram::~ShaderProgram() {
    glDeleteShader(vertex_id);
    glDeleteShader(fragment_id);
    glDeleteProgram(program_id);
}

