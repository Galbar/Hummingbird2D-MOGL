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
      \brief Constructor that allows to create a Camera with custom values. (Internal use only).
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
      (position - vec2(left, top))           (position + vec2(right, top))
             +----------------------------------------+
             |                                        |
             |                                        |
             |                                        |
             |                                        |
             |                                        |
             |                                        |
             +----------------------------------------+
      (position - vec2(left, bottom))        (position + vec2(right, bottom))
      \endcode

      Where `position` is the position of the camera and the normal of the plane
      is (center - position), where center is the point at which the camera is
      looking at.
     */
    void setOrthogonal(float left, float right, float bottom, float top);

    /*!
      \brief Set the position of the camera.
     */
    void setPosition(const hum::Vector3f& position);

    /*!
      \brief Get the position of the camera.
     */
    const hum::Vector3f& getPosition() const;

    /*!
      \brief Set the center of the camera. (Where it is looking at).
     */
    void setCenter(const hum::Vector3f& center);

    /*!
      \brief Get the center of the camera. (Where it is looking at).
     */
    const hum::Vector3f& getCenter() const;

    /*!
      \brief Set the up vector of the camera.
     */
    void setUp(const hum::Vector3f& up);

    /*!
      \brief Get the up vector of the camera.
     */
    const hum::Vector3f& getUp() const;

    /*!
      \brief Set the Z near of the camera.
     */
    void setZNear(float z_near);

    /*!
      \brief Get the Z near of the camera.
     */
    float getZNear() const;

    /*!
      \brief Set the Z far of the camera.
     */
    void setZFar(float z_far);

    /*!
      \brief Get the Z far of the camera.
     */
    float getZFar() const;

    /*!
      \brief Get the projection matrix of the camera. (Internal use only).
     */
    const glm::mat4& getProjection();

    /*!
      \brief Get the view matrix of the camera. (Internal use only).
     */
    const glm::mat4& getView();

    /*!
      \brief Return whether the projection marix has changed since the last
      getProjection(). (Internal use only).
     */
    bool projectionChanged() const;

    /*!
      \brief Return whether the view marix has changed since the last
      getView(). (Internal use only).
     */
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
  \brief The Camera is the device through which the player views the world.

  It is used by MultimediaOGL to render the game world.
*/
}
#endif
