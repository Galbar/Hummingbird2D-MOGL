#include "InputHandler.hpp"

namespace mogl
{
InputHandler::InputHandler()
{
    p_mouse_wheel_scrolled = false;
    auto p = sf::Mouse::getPosition();
    p_current_mouse_info.x = p.x;
    p_current_mouse_info.y = p.y;
    p_previous_mouse_info = p_current_mouse_info;
}
InputHandler::~InputHandler(){}

void InputHandler::update()
{
    keyUpdate();
    mouseUpdate();
    joystickUpdate();
}

void InputHandler::handleEvent(const sf::Event& event)
{
    if (keyEvent(event)) return;
    if (mouseEvent(event)) return;
    if (joystickEvent(event)) return;
}

bool InputHandler::isKeyPressed(sf::Keyboard::Key key)
{
    return p_key_pressed[key];
}

bool InputHandler::isKeyDown(sf::Keyboard::Key key)
{
    return p_key_down[key];
}

bool InputHandler::isKeyReleased(sf::Keyboard::Key key)
{
    return p_key_released[key];
}

bool InputHandler::mouseMoved()
{
    return p_mouse_move_event;
}

const InputHandler::MousePosition& InputHandler::getMouseCurrentPosition()
{
    return p_current_mouse_info;
}

const InputHandler::MousePosition& InputHandler::getMousePreviousPosition()
{
    return p_previous_mouse_info;
}

bool InputHandler::isMouseButtonPressed(sf::Mouse::Button button)
{
    return p_mouse_button_pressed[button];
}

bool InputHandler::isMouseButtonDown(sf::Mouse::Button button)
{
    return p_mouse_button_down[button];
}

bool InputHandler::isMouseButtonReleased(sf::Mouse::Button button)
{
    return p_mouse_button_released[button];
}

bool InputHandler::mouseWheelScrolled()
{
    return p_mouse_wheel_scrolled;
}

float InputHandler::getMouseWheelScrollDelta()
{
    return p_mouse_scroll_delta;
}

bool InputHandler::isJoystickConnected(unsigned int joystickId)
{
    return p_joystick_connected[joystickId];
}

bool InputHandler::isJoystickActive(unsigned int joystickId)
{
    return p_joystick_active[joystickId];
}

bool InputHandler::isJoystickDisconnected(unsigned int joystickId)
{
    return p_joystick_disconnected[joystickId];
}

bool InputHandler::isJoystickButtonPressed(unsigned int joystickId, unsigned int button)
{
    return p_joystick_button_pressed[std::pair<unsigned int, unsigned int>(joystickId, button)];
}

bool InputHandler::isJoystickButtonDown(unsigned int joystickId, unsigned int button)
{
    return p_joystick_button_down[std::pair<unsigned int, unsigned int>(joystickId, button)];
}

bool InputHandler::isJoystickButtonReleased(unsigned int joystickId, unsigned int button)
{
    return p_joystick_button_released[std::pair<unsigned int, unsigned int>(joystickId, button)];
}

float InputHandler::getJoystickAxisPosition(unsigned int joystickId, sf::Joystick::Axis axis)
{
    return p_joystick_axis_position[std::pair<unsigned int, unsigned int>(joystickId, axis)];
}

void InputHandler::keyUpdate()
{
    for (auto it = p_key_pressed.begin(); it != p_key_pressed.end(); ++it)
    {
        if (it->second)
        {
            p_key_down[it->first] = true;
            it->second = false;
        }
    }

    for (auto it = p_key_released.begin(); it != p_key_released.end(); ++it)
    {
        if (it->second)
            it->second = false;
    }
}

bool InputHandler::keyEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        p_key_pressed[event.key.code] = !p_key_down[event.key.code];
        p_key_released[event.key.code] = false;
        return true;
    }
    else if (event.type == sf::Event::KeyReleased)
    {
        p_key_pressed[event.key.code] = false;
        p_key_down[event.key.code] = false;
        p_key_released[event.key.code] = true;
        return true;
    }
    return false;
}

void InputHandler::mouseUpdate()
{
    p_mouse_move_event = false;

    for (auto it = p_mouse_button_pressed.begin(); it != p_mouse_button_pressed.end(); ++it)
    {
        if (it->second)
        {
            p_mouse_button_down[it->first] = true;
            it->second = false;
        }
    }

    for (auto it = p_mouse_button_released.begin(); it != p_mouse_button_released.end(); ++it)
    {
        if (it->second)
            it->second = false;
    }

    if (p_mouse_wheel_scrolled)
    {
        p_mouse_wheel_scrolled = false;
        p_mouse_scroll_delta = 0.0f;
    }
}

bool InputHandler::mouseEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        p_mouse_button_pressed[event.mouseButton.button] = !p_mouse_button_down[event.mouseButton.button];
        p_mouse_button_released[event.mouseButton.button] = false;
        return true;
    }
    else if (event.type == sf::Event::MouseButtonReleased)
    {
        p_mouse_button_pressed[event.mouseButton.button] = false;
        p_mouse_button_down[event.mouseButton.button] = false;
        p_mouse_button_released[event.mouseButton.button] = true;
        return true;
    }
    else if (event.type == sf::Event::MouseMoved)
    {
        p_previous_mouse_info = p_current_mouse_info;
        MousePosition mouse;
        mouse.x = event.mouseMove.x;
        mouse.y = event.mouseMove.y;
        p_current_mouse_info = mouse;
        p_mouse_move_event = true;
        return true;
    }
    else if (event.type == sf::Event::MouseWheelMoved)
    {
        p_mouse_wheel_scrolled = true;
        p_mouse_scroll_delta = event.mouseWheel.delta;
        return true;
    }
    return false;
}

void InputHandler::joystickUpdate()
{
    for (auto it = p_joystick_button_pressed.begin(); it != p_joystick_button_pressed.end(); ++it)
    {
        if (it->second)
        {
            p_joystick_button_down[it->first] = true;
            it->second = false;
        }
    }

    for (auto it = p_joystick_button_released.begin(); it != p_joystick_button_released.end(); ++it)
    {
        if (it->second)
            it->second = false;
    }

    for (auto it = p_joystick_connected.begin(); it != p_joystick_connected.end(); ++it)
    {
        if (it->second)
        {
            p_joystick_active[it->first] = true;
            it->second = false;
        }
    }

    for (auto it = p_joystick_disconnected.begin(); it != p_joystick_disconnected.end(); ++it)
    {
        if (it->second)
            it->second = false;
    }
}

bool InputHandler::joystickEvent(const sf::Event& event)
{
    if (event.type == sf::Event::JoystickConnected)
    {
        p_joystick_connected[event.joystickConnect.joystickId] = !p_joystick_active[event.joystickConnect.joystickId];
        p_joystick_disconnected[event.joystickConnect.joystickId] = false;
        return true;
    }
    else if (event.type == sf::Event::JoystickDisconnected)
    {
        p_joystick_connected[event.joystickConnect.joystickId] = false;
        p_joystick_active[event.joystickConnect.joystickId] = false;
        p_joystick_disconnected[event.joystickConnect.joystickId] = true;
        return true;
    }
    else if (event.type == sf::Event::JoystickButtonPressed)
    {
        std::pair<unsigned int, unsigned int> k(event.joystickButton.joystickId, event.joystickButton.button);
        p_joystick_button_pressed[k] = !p_joystick_button_down[k];
        p_joystick_button_released[k] = false;
        return true;
    }
    else if (event.type == sf::Event::JoystickButtonReleased)
    {
        std::pair<unsigned int, unsigned int> k(event.joystickButton.joystickId, event.joystickButton.button);
        p_joystick_button_pressed[k] = false;
        p_joystick_button_down[k] = false;
        p_joystick_button_released[k] = true;
        return true;
    }
    else if (event.type == sf::Event::JoystickMoved)
    {
        std::pair<unsigned int, unsigned int> k(event.joystickMove.joystickId, event.joystickMove.axis);
        p_joystick_axis_position[k] = event.joystickMove.position;
        return true;
    }
    return false;
}

}
