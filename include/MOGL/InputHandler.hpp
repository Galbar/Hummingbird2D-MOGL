#ifndef SFML_INPUT_HANDLER_HPP
#define SFML_INPUT_HANDLER_HPP
#include <unordered_map>
#include <SFML/Window.hpp>
#include "hash_pair.hpp"

namespace mogl
{
class InputHandler
{
public:
    struct MousePosition
    {
        MousePosition():
        x(0),y(0){}
        int x;
        int y;
    };
    InputHandler();
    ~InputHandler();

    void update();

    void handleEvent(const sf::Event& event);

    bool isKeyPressed(sf::Keyboard::Key key);

    bool isKeyDown(sf::Keyboard::Key key);

    bool isKeyReleased(sf::Keyboard::Key key);

    bool mouseMoved();

    const MousePosition& getMouseCurrentPosition();

    const MousePosition& getMousePreviousPosition();

    bool isMouseButtonPressed(sf::Mouse::Button button);

    bool isMouseButtonDown(sf::Mouse::Button button);

    bool isMouseButtonReleased(sf::Mouse::Button button);

    bool mouseWheelScrolled();

    float getMouseWheelScrollDelta();

    bool isJoystickConnected(unsigned int joystickId);

    bool isJoystickActive(unsigned int joystickId);

    bool isJoystickDisconnected(unsigned int joystickId);

    bool isJoystickButtonPressed(unsigned int joystickId, unsigned int button);

    bool isJoystickButtonDown(unsigned int joystickId, unsigned int button);

    bool isJoystickButtonReleased(unsigned int joystickId, unsigned int button);

    float getJoystickAxisPosition(unsigned int joystickId, sf::Joystick::Axis axis);

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
    MousePosition p_current_mouse_info;
    MousePosition p_previous_mouse_info;

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
}
#endif
