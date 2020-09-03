#include "Scene.h"

void Scene::addEntity(std::shared_ptr<Entity> _Entity)
{
	SceneEntities.push_back(_Entity);
}
