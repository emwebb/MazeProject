#include "VBO.hpp"


template<class T> VBO<T>::VBO() {
    
}

template<typename T> VBO<T>::VBO(GLenum target, T* data, int size, GLenum usage){
    if(typeid(T) == typeid(float)){
        type = GL_FLOAT;
    }
    this->target = target;
    glGenBuffers(1, &id); // Create the buffer.
    glBindBuffer(target, id); // Bind the buffer so we can use it.
    glBufferData(target, sizeof(T) * size, data, usage); // Send the data to the buffer.
}

template<typename T> VBO<T>::VBO(GLenum target, std::vector<T> data, GLenum usage){
    if(typeid(T) == typeid(float)){
        type = GL_FLOAT;
    }
    this->target = target;
    glGenBuffers(1, &id); // Create the buffer
    glBindBuffer(target, id); // Bind the buffer so we can use it.
    glBufferData(target, sizeof(T) * data.size(), data.data(), usage); // Send the data to the buffer.
}

template <typename T> void VBO<T>::insertVertexAttributeFormat(std::string variable_name, GLuint size, bool normalized, GLsizei stride,int offset){
    vertex_formats.insert(std::pair<std::string, vertex_format>(variable_name,{size,normalized,stride * (int)sizeof(T),offset * (int)sizeof(T)})); // This will be used when we need to set attribute pointers.
}

template<typename T> void VBO<T>::bind(ShaderProgram *program){
    glBindBuffer(target, id); //Bind the buffer so we can use it.
    
    for (const std::pair<std::string, vertex_format>& vetrex_format_pair : vertex_formats){// Go over all the attribute pointers and bind them to glsl variables and enable them.
        GLuint attribute_location = program->getAttributeLocation(vetrex_format_pair.first);
        if(attribute_location == -1) {
            logw("VBO","Attribute \"" + vetrex_format_pair.first + "\" does not exist in current shader program.");
        } else {
            glVertexAttribPointer(attribute_location, vetrex_format_pair.second.size, type, vetrex_format_pair.second.normalized, vetrex_format_pair.second.stride, (void*)vetrex_format_pair.second.offset);
            glEnableVertexAttribArray(attribute_location);
        }
    }
}
template<typename T> void VBO<T>::unbind(ShaderProgram *program){
    //Unbind everything!
    glBindBuffer(target, 0);
    for (const std::pair<std::string, vertex_format>& vetrex_format_pair : vertex_formats){
        GLuint attribute_location = program->getAttributeLocation(vetrex_format_pair.first);
        glDisableVertexAttribArray(attribute_location);
    }
}

template<typename T> VBO<T>::~VBO(){
    glDeleteBuffers(1, &id);
}

template class VBO<float>;
