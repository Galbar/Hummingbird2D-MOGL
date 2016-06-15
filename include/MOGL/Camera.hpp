#ifndef MOGL_CAMERA_HPP
#define MOGL_CAMERA_HPP
#include "glm.hpp"
#include "hummingbird/Vector3.hpp"

namespace mogl
{
class Camera
{
public:

    /*!
      \brief Default constructor.

      Constructs the camera with the following default values:
      \code
      mogl::Camera cam;
      cam.setZNear(0.1f);
      cam.setZFar(1000.f);
      cam.setOrthogonal(0, 100, 0, 100);
      cam.setPosition(hum::Vector3f(0, 0, -1));
      cam.setCenter(hum::Vector3f(0, 0, 1));
      cam.setUp(hum::Vector3f(0, -1, 0));
      \endcode
     */
    Camera ();

    /*!
      \brief Constructor that allows to create a Camera with custom values.

      Usage not recomended.
     */
    Camera (const glm::mat4& projection, const hum::Vector3f& position,
            const hum::Vector3f& center, const hum::Vector3f& up,
            float z_near, float z_far);

    /*!
      \brief Set the Camera to perspective projection.

      The perspective is defined by the given vertical field of view (fovy) and aspect
      ratio (aspect).

     */
    void setPerspective(float fovy, float aspect);

    /*!
      \brief Set the Camera to orthogonal projection.

      The rectangle of the view is formed by the points:
      \code
      (center - vec2(left, top))           (center + vec2(right, top))
             +----------------------------------------+
             |                                        |
             |                                        |
             |                                        |
             |                                        |
             |                                        |
             |                                        |
             +----------------------------------------+
      (center - vec2(left, bottom))        (center + vec2(right, bottom))
      \endcode
     */
    void setOrthogonal(float left, float right, float bottom, float top);
    const glm::mat4& getProjection();
    const glm::mat4& getView();
    void setPosition(const hum::Vector3f& position);
    const hum::Vector3f& getPosition() const;
    void setCenter(const hum::Vector3f& center);
    const hum::Vector3f& getCenter() const;
    void setUp(const hum::Vector3f& up);
    const hum::Vector3f& getUp() const;
    void setZNear(float z_near);
    float getZNear() const;
    void setZFar(float z_far);
    float getZFar() const;
    bool projectionChanged() const;
    bool viewChanged() const;

private:
    bool p_projection_changed, p_view_changed;
    float p_z_near, p_z_far;
    float p_param1, p_param2, p_param3, p_param4;
    bool p_is_ortho;
    hum::Vector3f p_position, p_center, p_up;
    glm::mat4 p_projection, p_view;
};

/*!
  \class mogl::Camera
  \brief The Camera is the device through wich the player views the world.

  It is used by MultimediaOGL to render the game world.
*/
}
#endif
