//
// Created by mk on 14.04.19.
//

#include "camera.h"
#include<helper.h>
camera::camera(int width, int height) : m_rotate_model(false)
{

    m_ratio = static_cast<float>(width / height);
    m_fov = 45.0f;
    m_model = glm::mat4x4();
    m_cam_pos = glm::vec3(-5, 5, 0);
    m_cam_front = glm::vec3(0, 0, 0);
    m_cam_up = glm::vec3(0, 1, 0);
    m_view = glm::lookAt(
            m_cam_pos,
            glm::vec3(0.f, 0.f, 0.f), // and looks at the origin
            glm::vec3(0, 0, 1)  // Head is up (set to 0,-1,0 to look upside-down)
    );
}

glm::mat4x4 camera::get_projection()
{
    m_projection = glm::perspective(glm::radians(m_fov), m_ratio, 1.f, 200.f);
    return m_projection;
}

glm::mat4x4 camera::get_view()
{
    m_view = glm::lookAt(
            m_cam_pos, // camera is at (4,3,3), in World Space
            m_cam_pos + m_cam_front,//point, // and looks at the origin
            m_cam_up  // Head is up (set to 0,-1,0 to look upside-down)
    );
    return m_view;
}

void camera::set_view(const glm::mat4x4& view)
{
    m_view = view;
}

glm::mat4x4 camera::get_model()
{
    return m_model;
}


glm::vec3 camera::get_center(const std::array<glm::vec3, 2>& rect) {
    const int UL = 0;
    const int LR = 1;

    return (rect[LR] + rect[UL]) / 2.0f;
}

void camera::focus_on(const std::array<glm::vec3, 2>& br)
{
    m_br = br;
    focus_point = get_center(br);
    float x = glm::distance(m_br[0], m_br[1]); //std::abs(std::max(m_br[0].x, m_br[1].x)) + std::abs(std::min(m_br[1].x, m_br[0].x));
    log_br(m_br);
    m_cam_pos = glm::vec3(0, 0, 10) -focus_point; //glm::vec3(0,0, -focus_point);
    m_cam_front = glm::vec3(0,0,-1); //glm::vec3(0,0, -focus_point);
    log_vertex(m_cam_pos);
    m_view = glm::lookAt(
            m_cam_pos, // camera is at (4,3,3), in World Space
            m_cam_pos + m_cam_front,//point, // and looks at the origin
            m_cam_up  // Head is up (set to 0,-1,0 to look upside-down)
    );
    m_model = glm::translate(m_model, -focus_point);
}

void camera::setScreenRatio(float r)
{
    m_ratio = r;
}

void camera::rotate(const glm::quat& q)
{
    //m_model = m_model * glm::toMat4(q) ;
    if (!m_rotate_model)
    {
        m_cam_front = glm::rotate(q, m_cam_front);
    }
    else {
        m_model = glm::toMat4(q) * m_model;
    }
}

void camera::move(const glm::vec3& direction)
{
    // Todo : Implement movement

    //m_model = glm::translate(m_model, direction);
    log_vertex(direction);
    m_cam_pos += direction;
    m_view = glm::lookAt(
            m_cam_pos, // camera is at (4,3,3), in World Space
            m_cam_pos + m_cam_front,//point, // and looks at the origin
            m_cam_up  // Head is up (set to 0,-1,0 to look upside-down)
    );
}

void camera::zoom(const float factor)
{
    const float max_angle_ov = 70.0f;
    if (m_fov >= 1.0f && m_fov <= max_angle_ov)
        m_fov -= factor;
    if (m_fov <= 1.0f)
        m_fov = 1.0f;
    if (m_fov >= max_angle_ov)
        m_fov = max_angle_ov;
}

void camera::reset()
{
    m_view = glm::lookAt(
            m_cam_pos, // camera is at (4,3,3), in World Space
            glm::vec3(0, 0, 0),//point, // and looks at the origin
            glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
    m_model = glm::translate(glm::mat4(1.0f), -focus_point);
}

void camera::set_model_rotate(bool ok /*= true*/)
{
    m_rotate_model = ok;
}
