#ifndef _SCENE_H
#define _SCENE_H

#include <iostream>
#include <vector>
#include "Core.h"
#include "RigidBodyComponent.h"
#include <reactphysics3d/reactphysics3d.h>

class Entity;

class Scene {
public:
	friend Core;

	static auto createWorldPhysicsSettings() 
	{
		rp3d::PhysicsWorld::WorldSettings prop;
		return prop;
	}

	void addEntity(std::shared_ptr<Entity> _Entity);
	void addPhysicsWorld();
	void addPhysicsWorld(rp3d::PhysicsWorld::WorldSettings _prop);

	inline rp3d::PhysicsWorld* getPhysicsWorld() { return world; }

	Scene();
	~Scene();
private:
	std::vector<std::shared_ptr<Entity>> SceneEntities;
	rp3d::PhysicsCommon physicsCommon;
	rp3d::PhysicsWorld* world = nullptr;
};
#endif