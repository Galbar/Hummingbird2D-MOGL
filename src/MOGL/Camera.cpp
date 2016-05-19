#include "Camera.hpp"

namespace mogl
{
Camera::Camera ():
Camera(glm::ortho(0, 100, 0, 100), hum::Vector3f(0, 0, -1), hum::Vector3f(0, 0, 1),
        hum::Vector3f(0, -1, 0), 0.1f, 1000.f)
{}

Camera::Camera (const glm::mat4& projection, const hum::Vector3f& position,
        const hum::Vector3f& center, const hum::Vector3f& up,
        float z_near, float z_far):
p_projection_changed(true),
p_view_changed(true),
p_z_near(z_near),
p_z_far(z_far),
p_position(position),
p_center(center),
p_up(up),
p_projection(projection)
{}

void Camera::setPerspective(float fovy, float aspect)
{
    setProjection(glm::perspective(fovy, aspect, p_z_near, p_z_far));
}

void Camera::setOrthogonal(float left, float right, float bottom, float top)
{
    setProjection(glm::ortho(left, right, bottom, top, p_z_near, p_z_far));
}

void Camera::setProjection(const glm::mat4& projection)
{
    p_projection_changed = true;
    p_projection = projection;
}

const glm::mat4& Camera::getProjection()
{
    p_projection_changed = false;
    return p_projection;
}

const glm::mat4& Camera::getView()
{
    if (p_view_changed)
    {
        p_view_changed = false;
        p_view = glm::lookAt(humToGlm(p_position), humToGlm(p_center), humToGlm(p_up));
    }
    return p_view;
}

void Camera::setPosition(const hum::Vector3f& position)
{
    p_view_changed = true;
    p_position = position;
}

const hum::Vector3f& Camera::getPosition() const
{
    return p_position;
}

void Camera::setCenter(const hum::Vector3f& center)
{
    p_view_changed = true;
    p_center = center;
}

const hum::Vector3f& Camera::getCenter() const
{
    return p_center;
}

void Camera::setUp(const hum::Vector3f& up)
{
    p_view_changed = true;
    p_up = up;
}

const hum::Vector3f& Camera::getUp() const
{
    return p_up;
}

void Camera::setZNear(float z_near)
{
    p_view_changed = true;
    p_z_near = z_near;
}

float Camera::getZNear() const
{
    return p_z_near;
}

void Camera::setZFar(float z_far)
{
    p_view_changed = true;
    p_z_far = z_far;
}

float Camera::getZFar() const
{
    return p_z_far;
}

bool Camera::projectionChanged() const
{
    return p_projection_changed;
}

bool Camera::viewChanged() const
{
    return p_view_changed;
}
}
