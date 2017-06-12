#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ShaderProgram.hpp"

float vertex[] = {
    -0.5f, -0.5f,
     0.5f, -0.5f,
     0.5f,  0.5f,
    -0.5f,  0.5f
};

int main(){
    
    // initialize GLFW
    if(glfwInit() == GL_FALSE){
        std::cerr << "Can't initialize GLFW" << std::endl;
        return 1;
    }
    
    atexit(glfwTerminate);
    
    // choose OpenGL Version 3.2 Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // create window
    GLFWwindow* const window(glfwCreateWindow(640, 480, "Hello, world!", NULL, NULL));
    if(window == NULL){
        std::cerr << "Can't create GLFW window" << std::endl;
        return 1;
    }
    
    glfwMakeContextCurrent(window);
    
    // initialize GLEW
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK){
        std::cerr << "Can't initialize GLEW" << std::endl;
        return 1;
    }
    
    glfwSwapInterval(1);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

    ShaderProgram shaderProgram;
    const GLuint program(shaderProgram.loadProgram("shaders/shader.vert", "shaders/shader.frag"));
    
    shaderProgram.initVertex(2, 4, vertex);
    
    while(glfwWindowShouldClose(window) == GL_FALSE){
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(program);
        
        shaderProgram.draw();
        
        glfwSwapBuffers(window);
        glfwWaitEvents();
    }
    
    shaderProgram.deleteVertex();
}
