#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class ShaderProgram{
public:
    ShaderProgram();
    ~ShaderProgram();
    
    GLboolean printShaderInfoLog(GLuint shader, const char* str);
    GLboolean printProgramInfoLog(GLuint program);
    GLuint createProgram(const char* vsrc, const char* fsrc);
    GLboolean readShaderSource(const char* name, std::vector<GLchar> &buffer);
    GLuint loadProgram(const char* vert, const char* frag);
    
    void initVertex(GLint dimension, GLuint vertexcount, const float* vertex);
    void deleteVertex();
    void draw();
    
private:
    GLuint vao;
    GLuint vbo;
};
