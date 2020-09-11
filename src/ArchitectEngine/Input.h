#ifndef _INPUT_H
#define  _INPUT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Component.h"

///This class handles inputs.
///
///This class handles whether keys are pressed, released or held, and is used within InputComponent.
///class Entity;
class Input : Component
{
public:
	///This method checks if a key is held.
	///
	///This method checks to see if a key has been held for more than one tick.
	///@param _key This is the key to check for.
	bool isKey(int _key);
	///This method checks if a key is pressed.
	///
	///This method checks to see if a key has been pressed.
	///@param _key This is the key to check for.
	bool isKeyPressed(int _key);
	///This method checks if a key is released.
	///
	///This method checks to see if a key has been released for more than one tick.
	///@param _key This is the key to check for.
	bool isKeyReleased(int _key);

	///This method checks for input from SDL and stores the key's.
	///
	///This method checks for SDL events and stores the key's if they are pressed.
	///@param window
	///@param _window This is the event to check for.
	void static handleInput(GLFWwindow* window, int key, int scancode, int action, int mods);

	void static mouse_callback(GLFWwindow* window, double xpos, double ypos);
private:
	static std::vector<int> keys, pressedKeys, releasedKeys;
	static bool firstMouse;
	static float yaw;
	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	static float pitch;
	static float lastX;
	static float lastY;
	static float fov;
};

#endif
