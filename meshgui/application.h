//
// Created by mk on 14.04.19.
//

#pragma once

#include <string>
#include <vector>
#include "meshtype.h"
#include "helper.h"
#include "shader.h"
#include "camera.h"
#include <spdlog/logger.h>
#include <GLFW/glfw3.h>

class application_exception : public std::exception {
public:
    explicit application_exception(const std::string& msg) : m_msg(msg){ }

    virtual const char* what() const throw() {
        return m_msg.c_str();
    }

private:
    std::string m_msg;
};

class application {
public:
    application(const std::string& title, int width, int height);
    ~application();
    void run();
    void load_shaders(const std::string& fragment, const std::string& vertex);
    enum class Action {
        nop = 0,
        rotate = 1,
        move = 2,
        zoom = 3
    };

    void set_workdir(std::string& dir) {m_work_dir = dir;};
    void on_move(GLFWwindow* w, double x, double y);
    void on_scroll(GLFWwindow* w, double x, double y);
    void on_click(GLFWwindow* w, int a, int b, int m);
    void on_key(GLFWwindow* w, int key, int scancode, int action, int mods);
    void on_char(GLFWwindow* w, unsigned int c);
    void on_fb_resize(GLFWwindow* w, int width, int height);

private:
    void set_mesh(const mesh::mesh_type& a_mesh) { m_mesh = a_mesh; initialize(); };
    void initialize();
    glm::vec3 to_screen_coord(double x, double y);

    std::string m_title;
    int m_width;
    int m_height;
    std::string m_work_dir;
    bool m_initialized;
    int m_mouse_action;
    camera m_cam;
    shader m_shader;
    GLFWwindow* m_window;
    std::shared_ptr<spdlog::logger> m_logger;
    mesh::mesh_type m_mesh;
};



