#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include "libgame.h"
#include <vector>
#include <unordered_map>
namespace libgame {
    
    namespace InputManager {
        namespace Key {
            static int stateBuffer[GLFW_KEY_LAST + 1] = { GLFW_RELEASE };
            static int state[GLFW_KEY_LAST + 1] = { GLFW_RELEASE };
            namespace { 
                bool _cacheValid = true; 
            }
            static int modifiers = 0;
            void Callback(GLFWwindow* window, int key, int scancode, int action, int mods);

            void StateUpdate();
            bool GetKey(int keyCode);

            bool GetKeyDown(int keyCode);

            bool GetKeyUp(int keyCode);
        }
        
        namespace Mouse {
            static int stateBuffer[GLFW_MOUSE_BUTTON_LAST + 1] = { GLFW_RELEASE };
            static int state[GLFW_MOUSE_BUTTON_LAST + 1] = { GLFW_RELEASE };
            
            namespace { bool _cacheValid = true; }
            static int modifiers = 0;
            void ButtonCallback(Window* window, int button, int action, int mods);
            static Vector2 scrollDelta(0, 0);
            void ScrollCallback(Window* window, double xoffset, double yoffset);

            void StateUpdate();

            /// <summary>
            /// Test if the button is held down.
            /// </summary>
            /// <param name="buttonCode"></param>
            /// <returns></returns>
            bool GetKey(int buttonCode);

            /// <summary>
            /// Test if the button was just pressed down.
            /// </summary>
            /// <param name="buttonCode"></param>
            /// <returns></returns>
            bool GetKeyDown(int buttonCode);

            /// <summary>
            /// Test if the button was just released.
            /// </summary>
            /// <param name="buttonCode"></param>
            /// <returns></returns>
            bool GetKeyUp(int buttonCode);
        }

        namespace Cursor {
            

            static Vector2 position(0, 0);
            void PositionCallback(GLFWwindow* window, double xpos, double ypos);

            bool EnableRawMouseMotion(GLFWwindow* window);
            void DisableRawMouseMotion(GLFWwindow* window);
            void DisableCursor(GLFWwindow* window);

            void EnableCursor(GLFWwindow* window);

            void HideCursor(GLFWwindow* window);

            
            

        }

    }



}
#endif