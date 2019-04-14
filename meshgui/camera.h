//
// Created by mk on 14.04.19.
//

#pragma once


#pragma once
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include<glm/gtx/quaternion.hpp>
#include <array>

class camera
{
public:
    camera(int width = 4, int height = 3);
    ~camera() {};

    glm::mat4x4 get_projection();
    glm::mat4x4 get_view();
    glm::mat4x4 get_model();
    void set_view(const glm::mat4x4& view);
    void focus_on(const std::array<glm::vec3, 2>& br);
    void setScreenRatio(float r);
    void rotate(const glm::quat& q);
    void move(const glm::vec3& direction);
    void zoom(const float factor);
    void reset();
    void set_model_rotate(bool ok = false);
private:
    glm::vec3 get_center(const std::array<glm::vec3, 2>& br);
    glm::mat4x4 m_view;
    glm::mat4x4 m_projection;
    glm::mat4x4 m_model;
    glm::vec3 focus_point;
    glm::vec3 m_cam_pos;
    glm::vec3 m_cam_front;
    glm::vec3 m_cam_up;
    std::array<glm::vec3, 2> m_br;
    float m_ratio;
    float m_fov;
    bool m_rotate_model;
};



