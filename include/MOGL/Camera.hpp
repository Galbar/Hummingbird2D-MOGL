#ifndef MOGL_CAMERA_HPP
#define MOGL_CAMERA_HPP
#include "glm.hpp"

namespace mogl
{
class Camera
{
public:
    Camera ();
    Camera (const glm::mat4& projection, const glm::vec3& position,
            const glm::vec3& center, const glm::vec3& up,
            float z_near, float z_far);

    void setPerspective(float fovy, float aspect);
    void setOrthogonal(float left, float right, float bottom, float top);
    const glm::mat4& getProjection();
    const glm::mat4& getView();
    void setPosition(const glm::vec3& position);
    const glm::vec3& getPosition() const;
    void setCenter(const glm::vec3& center);
    const glm::vec3& getCenter() const;
    void setUp(const glm::vec3& up);
    const glm::vec3& getUp() const;
    void setZNear(float z_near);
    float getZNear() const;
    void setZFar(float z_far);
    float getZFar() const;
    bool projectionChanged() const;
    bool viewChanged() const;

private:
    void setProjection(const glm::mat4& projection);
    bool p_projection_changed, p_view_changed;
    float p_z_near, p_z_far;
    glm::vec3 p_position, p_center, p_up;
    glm::mat4 p_projection, p_view;
};
}
#endif
