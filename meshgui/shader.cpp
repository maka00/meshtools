//
// Created by mk on 14.04.19.
//

#include<shader.h>
#include<fstream>
#include<glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
shader::shader()
{
    m_handle = 0;
    m_linked = false;
}

shader::~shader()
{
}

void shader::load_program(const std::string& filename, GLSLShaderType type)
{
    if (m_handle == 0) {
        m_handle = glCreateProgram();
    }
    std::ifstream f(filename);
    std::string shader_source = std::string((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
    const char *shader_str = shader_source.c_str();
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &shader_str, nullptr);
    glCompileShader(shader);
    glAttachShader(m_handle, shader);
}

void shader::link()
{
    m_linked = true;
    glLinkProgram(m_handle);
    int result;
    glGetProgramiv(m_handle, GL_LINK_STATUS, &result);
    if (result == GL_FALSE) {
        m_linked = false;
    }
}

int shader::get_handle()
{
    return m_handle;
}

bool shader::is_linked()
{
    return m_linked;
}

void shader::use()
{
    glUseProgram(m_handle);
}

void shader::bind_attrib_location(GLuint location, const std::string & name)
{
}

void shader::set_uniform(const std::string& name, const glm::vec3 & v)
{
    GLint loc = glGetUniformLocation(m_handle, name.c_str());
    glUniform3fv(loc, 1, reinterpret_cast<const GLfloat*>(glm::value_ptr(v)));
}

void shader::set_uniform(const std::string& name, const glm::vec4 & v)
{
    GLint loc = glGetUniformLocation(m_handle, name.c_str());
    glUniform4fv(loc, 1, reinterpret_cast<const GLfloat*>(glm::value_ptr(v)));
}

void shader::set_uniform(const std::string& name, const glm::mat3 & v)
{
    GLint loc = glGetUniformLocation(m_handle, name.c_str());
    glUniformMatrix3fv(loc, 1,GL_FALSE, reinterpret_cast<const GLfloat*>(glm::value_ptr(v)));
}

void shader::set_uniform(const std::string& name, const glm::mat4 & v)
{
    GLint loc = glGetUniformLocation(m_handle, name.c_str());
    glUniformMatrix4fv(loc, 1,GL_FALSE, reinterpret_cast<const GLfloat*>(glm::value_ptr(v)));
}

void shader::set_uniform(const std::string& name, int v)
{
    GLint loc = glGetUniformLocation(m_handle, name.c_str());
    glUniform1i(loc,v);
}

void shader::set_uniform(const std::string& name, bool v)
{
    GLuint loc = glGetUniformLocation(m_handle, name.c_str());
    glUniform1i(loc,v);
}

