#ifndef _SCENEMANAGER_H
#define _SCENEMANAGER_H

#include <iostream>
#include <vector>
#include "Core.h"
#include "Scene.h"

class SceneManager {
public:
	friend Core;

	void setActiveScene(std::shared_ptr<Scene> _scene);

private:
	std::shared_ptr<Scene> activeScene;
};
#endif