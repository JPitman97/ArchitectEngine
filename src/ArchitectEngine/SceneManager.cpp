#include "SceneManager.h"

void SceneManager::setActiveScene(std::shared_ptr<Scene> _scene)
{
	activeScene = _scene;
}
