//
// Created by mk on 14.04.19.
//

#pragma once

#include <string>
#include<unordered_map>
#include <glad/glad.h>
#include<glm/glm.hpp>

class shader {
public:
    enum GLSLShaderType {
        VERTEX = GL_VERTEX_SHADER,
        FRAGMENT = GL_FRAGMENT_SHADER
    };

    shader();
    ~shader();
    void load_program(const std::string& filename, GLSLShaderType type);
    void link();
    int get_handle();
    bool is_linked();
    void use();

    void bind_attrib_location(GLuint location, const std::string & name);
    void set_uniform(const std::string& name, const glm::vec3 & v);
    void set_uniform(const std::string& name, const glm::vec4 & v);
    void set_uniform(const std::string& name, const glm::mat3 & v);
    void set_uniform(const std::string& name, const glm::mat4 & v);
    void set_uniform(const std::string& name, int v);
    void set_uniform(const std::string& name, bool v);
private:
    int m_handle;
    bool m_linked;
    std::unordered_map<std::string, int> m_uniform_locations;
};



