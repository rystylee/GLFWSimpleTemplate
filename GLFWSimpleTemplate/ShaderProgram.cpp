#include "ShaderProgram.hpp"

ShaderProgram::ShaderProgram() : vao(0), vbo(0){
}

ShaderProgram::~ShaderProgram(){
}

GLboolean ShaderProgram::printShaderInfoLog(GLuint shader, const char* str){
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE) std::cerr << "Compile Error in " << str << std::endl;
    
    GLsizei bufSize;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &bufSize);
    
    if(bufSize > 1){
        std::vector<GLchar> infoLog(bufSize);
        GLsizei length;
        glGetShaderInfoLog(shader, bufSize, &length, &infoLog[0]);
        std::cerr << &infoLog[0] << std::endl;
    }
    
    return static_cast<GLboolean>(status);
}

GLboolean ShaderProgram::printProgramInfoLog(GLuint program){
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if(status == GL_FALSE) std::cerr << "Link Error." << std::endl;
    
    GLsizei bufSize;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufSize);
    
    if(bufSize > 1){
        std::vector<GLchar> infoLog(bufSize);
        GLsizei length;
        glGetProgramInfoLog(program, bufSize, &length, &infoLog[0]);
        std::cerr << &infoLog[0] << std::endl;
    }
    
    return static_cast<GLboolean>(status);
}

GLuint ShaderProgram::createProgram(const char* vsrc, const char* fsrc){
    const GLuint program(glCreateProgram());
    
    if(vsrc != NULL){
        const GLuint vobj(glCreateShader(GL_VERTEX_SHADER));
        glShaderSource(vobj, 1, &vsrc, NULL);
        glCompileShader(vobj);
        if(printShaderInfoLog(vobj, "vertex shader")) glAttachShader(program, vobj);
        glDeleteShader(vobj);
    }
    
    if(fsrc != NULL){
        const GLuint fobj(glCreateShader(GL_FRAGMENT_SHADER));
        glShaderSource(fobj, 1, &fsrc, NULL);
        glCompileShader(fobj);
        if(printShaderInfoLog(fobj, "fragment shader")) glAttachShader(program, fobj);
        glDeleteShader(fobj);
    }
    
    glBindAttribLocation(program, 0, "position");
    glBindFragDataLocation(program, 0, "outputColor");
    glLinkProgram(program);
    
    if(printProgramInfoLog(program)) return program;
    
    glDeleteProgram(program);
    return 0;
}

GLboolean ShaderProgram::readShaderSource(const char* name, std::vector<GLchar> &buffer){
    if(name == NULL) return false;
    
    std::ifstream file(name, std::ios::binary);
    if(file.fail()){
        std::cerr << "Error: Can't open source file: " << name << std::endl;
        return false;
    }
    
    file.seekg(0L, std::ios::end);
    GLsizei length = static_cast<GLsizei>(file.tellg());
    
    buffer.resize(length+1);
    
    file.seekg(0L, std::ios::beg);
    file.read(buffer.data(), length);
    buffer[length] = '\0';
    
    if(file.fail()){
        std::cerr << "Error: Could not read source file: " << name << std::endl;
        file.close();
        return false;
    }
    
    file.close();
    return true;
}


GLuint ShaderProgram::loadProgram(const char* vert, const char* frag){
    std::vector<GLchar> vsrc;
    const bool vstat(readShaderSource(vert, vsrc));
    std::vector<GLchar> fsrc;
    const bool fstat(readShaderSource(frag, fsrc));
    
    return vstat && fstat ? createProgram(vsrc.data(), fsrc.data()) : 0;
}

void ShaderProgram::initVertex(GLint dimension, GLuint vertexcount, const float* vertex){
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, dimension * vertexcount * sizeof(float), vertex, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, dimension, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
}

void ShaderProgram::deleteVertex(){
    glDeleteBuffers(1, &vao);
    glDeleteBuffers(1, &vbo);
}

void ShaderProgram::draw(){
    glBindVertexArray(vao);
    glDrawArrays(GL_LINE_LOOP, 0, 4);
}
