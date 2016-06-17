#ifndef SFML_INPUT_HANDLER_HPP
#define SFML_INPUT_HANDLER_HPP
#include <unordered_map>
#include <SFML/Window.hpp>
#include "hummingbird/Vector2.hpp"
#include "hash_pair.hpp"

namespace mogl
{
class InputHandler
{
public:
    //! Class constructor
    InputHandler();

    //! Class destructor
    ~InputHandler();

    /*!
      \brief Run one update step.

      This method must be ran once per logical update cycle as it takes care
      of updating, for example, when a key that was _just pressed_ passes to being
      _kept pressed_.
     */
    void update();

    /*!
      \brief Handle a new event.

      Every sf::Event polled from the sf::Window must be passed to this method.
      It takes care of treating it.
     */
    void handleEvent(const sf::Event& event);

    /*!
      @{
      \name Keyboard
     */

    //! Get whether a given key has been just pressed.
    bool isKeyPressed(sf::Keyboard::Key key);

    //! Get whether a given key has been kept pressed.
    bool isKeyDown(sf::Keyboard::Key key);

    //! Get whether a given key has been just released.
    bool isKeyReleased(sf::Keyboard::Key key);

    /*!
      @}
      @{
      \name Mouse
     */

    //! Get wheter the mouse just moved.
    bool mouseMoved();

    //! Get the current position of the mouse.
    const hum::Vector2i& getMouseCurrentPosition();

    //! Get the previous position of the mouse.
    const hum::Vector2i& getMousePreviousPosition();

    //! Get if a given mouse button has been just pressed.
    bool isMouseButtonPressed(sf::Mouse::Button button);

    //! Get if a given mouse button has been kept pressed.
    bool isMouseButtonDown(sf::Mouse::Button button);

    //! Get if a given mouse button has been just released.
    bool isMouseButtonReleased(sf::Mouse::Button button);

    //! Get if the mouse wheel has just been scrolled.
    bool mouseWheelScrolled();

    //! Get the amount that the mouse wheel has been scrolled.
    float getMouseWheelScrollDelta();

    /*!
      @}
      @{
      \name JoyStick
     */

    //! Check whether a JoyStick is connected.
    bool isJoystickConnected(unsigned int joystickId);

    //! Check whether a JoyStick is active.
    bool isJoystickActive(unsigned int joystickId);

    //! Check whether a JoyStick is disconnected.
    bool isJoystickDisconnected(unsigned int joystickId);

    //! Check whether a button of a JoyStick has been just pressed.
    bool isJoystickButtonPressed(unsigned int joystickId, unsigned int button);

    //! Check whether a button of a JoyStick has been kept pressed.
    bool isJoystickButtonDown(unsigned int joystickId, unsigned int button);

    //! Check whether a button of a JoyStick has been just released.
    bool isJoystickButtonReleased(unsigned int joystickId, unsigned int button);

    //! Get the position of an Axis of a given JoyStick
    float getJoystickAxisPosition(unsigned int joystickId, sf::Joystick::Axis axis);

    //! @}

private:
    void keyUpdate();

    bool keyEvent(const sf::Event& event);

    std::unordered_map<unsigned int, bool> p_key_pressed;
    std::unordered_map<unsigned int, bool> p_key_down;
    std::unordered_map<unsigned int, bool> p_key_released;

    void mouseUpdate();

    bool mouseEvent(const sf::Event& event);

    bool p_mouse_move_event;
    bool p_mouse_wheel_scrolled;
    float p_mouse_scroll_delta;
    hum::Vector2i p_current_mouse_info;
    hum::Vector2i p_previous_mouse_info;

    std::unordered_map<unsigned int, bool> p_mouse_button_pressed;
    std::unordered_map<unsigned int, bool> p_mouse_button_down;
    std::unordered_map<unsigned int, bool> p_mouse_button_released;

    void joystickUpdate();

    bool joystickEvent(const sf::Event& event);

    std::unordered_map<unsigned int, bool> p_joystick_connected;
    std::unordered_map<unsigned int, bool> p_joystick_active;
    std::unordered_map<unsigned int, bool> p_joystick_disconnected;
    std::unordered_map<std::pair<unsigned int, unsigned int>, bool> p_joystick_button_pressed;
    std::unordered_map<std::pair<unsigned int, unsigned int>, bool> p_joystick_button_down;
    std::unordered_map<std::pair<unsigned int, unsigned int>, bool> p_joystick_button_released;
    std::unordered_map<std::pair<unsigned int, unsigned int>, float> p_joystick_axis_position;
};

/*!
  \class mogl::InputHandler
  \brief Class that handles SFML input events and allows for easy quering of
  related data.
*/
}
#endif
