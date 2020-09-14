#ifndef _RIGIDBODY_H
#define _RIGIDBODY_H

#include <iostream>
#include <glm/gtc/quaternion.hpp>
#include "Component.h"
#include <reactphysics3d/reactphysics3d.h>

class RigidBodyComponent : public Component{
public:
	static enum RIGIDBODYTYPE
	{
		STATIC,
		KINEMATIC,
		DYNAMIC
	};
	static enum COLLIDERTYPE
	{
		BOX,
		SPHERE
	};

	RigidBodyComponent();

	void initialise();

	void onTick() override;

	void setType(RIGIDBODYTYPE _rbType);
	inline void setBounciness(float _bounciness) 
	{
		rigidBody->getCollider(0)->getMaterial().setBounciness(_bounciness);
	}
	inline void setMass(float _mass)
	{
		rigidBody->getCollider(0)->getMaterial().setMassDensity(_mass);
	}

	void addCollider(COLLIDERTYPE _colType, glm::vec3 _size);

	~RigidBodyComponent() override;
private:
	rp3d::RigidBody* rigidBody = nullptr;
	rp3d::PhysicsWorld* world = nullptr;
	rp3d::PhysicsCommon physicsCommon;
	bool stop = false;
};
#endif