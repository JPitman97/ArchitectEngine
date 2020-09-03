#ifndef _SCENE_H
#define _SCENE_H

#include <iostream>
#include <vector>
#include "Core.h"

class Entity;

class Scene {
public:
	friend Core;
	void addEntity(std::shared_ptr<Entity> _Entity);

private:
	std::vector<std::shared_ptr<Entity>> SceneEntities;
};
#endif