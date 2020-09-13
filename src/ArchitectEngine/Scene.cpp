#include "Scene.h"

void Scene::addEntity(std::shared_ptr<Entity> _Entity)
{
	SceneEntities.push_back(_Entity);
}

void Scene::addPhysicsWorld()
{
	world = physicsCommon.createPhysicsWorld();
}

void Scene::addPhysicsWorld(rp3d::PhysicsWorld::WorldSettings _prop)
{
	world = physicsCommon.createPhysicsWorld(_prop);
}

Scene::Scene()
{
	world = physicsCommon.createPhysicsWorld();
}

Scene::~Scene()
{
	int x = world->getNbRigidBodies();
	for (int i = 0; i < x; i++)
	{
		auto rb = world->getRigidBody(0);
		world->destroyRigidBody(rb);
	}
	physicsCommon.destroyPhysicsWorld(world);
}
