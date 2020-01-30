#include "Input.h"
#include "Core.h"
#include "Camera.h"
#include "Entity.h"
#include <iostream>

// global members
std::vector<int> Input::keys, Input::pressedKeys, Input::releasedKeys;
bool Input::firstMouse = true;
float Input::yaw = -90.0f;
// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float Input::pitch = 0.0f;
float Input::lastX = 800.0f / 2.0;
float Input::lastY = 600.0 / 2.0;
float Input::fov = 45.0f;

bool Input::isKey(int _key)
{
	for (auto& k : keys)
		if (k == _key)
			return true;

	return false;
}

bool Input::isKeyPressed(int _key)
{
	for (auto& k : pressedKeys)
		if (k == _key)
			return true;

	return false;
}

bool Input::isKeyReleased(int _key)
{
	for (auto& k : releasedKeys)
		if (k == _key)
			return true;

	return false;
}

void Input::handleInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	pressedKeys.clear();
	releasedKeys.clear();

	switch (action)
	{
	case GLFW_PRESS:
		if (glfwGetKey(window, key))
			std::cout << "Key pressed: " << static_cast<char>(key) << std::endl;
		pressedKeys.push_back(key);
		if (std::find(keys.begin(), keys.end(), key) != keys.end()) {
			//Do nothing
			std::cout << "Ignoring key: " << static_cast<char>(key) << std::endl;
		}
		else
			keys.push_back(key);

		break;
	case GLFW_RELEASE:
		std::cout << "Key released: " << static_cast<char>(key) << std::endl;
		releasedKeys.push_back(key);
		for (int i = 0; i < keys.size(); i++)
		{
			if (keys.at(i) == key)
				keys.erase(keys.begin() + i);
		}
		break;
	default: ;
	}
}

void Input::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	auto core = reinterpret_cast<Core*>(glfwGetWindowUserPointer(window));
	core->getCamera()->processMouseMovement(xoffset, yoffset, GL_TRUE);
}
