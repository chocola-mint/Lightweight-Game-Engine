#include "libgameInputManager.h"

using namespace libgame::InputManager;

void Key::Callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    stateBuffer[key] = action;
    modifiers = mods;
    _cacheValid = false;
}

void Key::StateUpdate() {
    if (!_cacheValid)
        for (int i = 0; i < GLFW_KEY_LAST + 1; ++i){
            state[i] = stateBuffer[i];
            _cacheValid = true;
        }
}

bool Key::GetKey(int keyCode) {
    return stateBuffer[keyCode] != GLFW_RELEASE;
}

bool Key::GetKeyDown(int keyCode) {
    return stateBuffer[keyCode] != GLFW_RELEASE && state[keyCode] == GLFW_RELEASE;
}

bool Key::GetKeyUp(int keyCode) {
    return state[keyCode] != GLFW_RELEASE && stateBuffer[keyCode] == GLFW_RELEASE;
}

void Mouse::ButtonCallback(Window* window, int button, int action, int mods)
{
    stateBuffer[button] = action;
    modifiers = mods;
    _cacheValid = false;
}

void Mouse::ScrollCallback(Window* window, double xoffset, double yoffset) {
    scrollDelta.x = xoffset;
    scrollDelta.y = yoffset;
}

void Mouse::StateUpdate() {
    if (!_cacheValid)
    {
        for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST + 1; ++i)
            state[i] = stateBuffer[i];
        _cacheValid = true;
    }
}

bool Mouse::GetKey(int buttonCode) {
    return stateBuffer[buttonCode] != GLFW_RELEASE;
}

bool Mouse::GetKeyDown(int buttonCode) {
    return stateBuffer[buttonCode] != GLFW_RELEASE && state[buttonCode] == GLFW_RELEASE;
}

bool Mouse::GetKeyUp(int buttonCode) {
    return state[buttonCode] != GLFW_RELEASE && stateBuffer[buttonCode] == GLFW_RELEASE;
}

void Cursor::PositionCallback(GLFWwindow* window, double xpos, double ypos) {
    position.x = xpos;
    position.y = ypos;
}

bool Cursor::EnableRawMouseMotion(GLFWwindow* window) {
    if (!glfwRawMouseMotionSupported()) return false;
    glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    return true;
}

void Cursor::DisableRawMouseMotion(GLFWwindow* window) {
    glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
}

void Cursor::DisableCursor(GLFWwindow* window) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Cursor::EnableCursor(GLFWwindow* window) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Cursor::HideCursor(GLFWwindow* window) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}