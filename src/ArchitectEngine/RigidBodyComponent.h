#ifndef _RIGIDBODY_H
#define _RIGIDBODY_H

#include <iostream>
#include "Component.h"
#include <reactphysics3d/reactphysics3d.h>

class RigidBodyComponent : public Component{
public:
	RigidBodyComponent();

	void Init();

	~RigidBodyComponent() override;
private:
	rp3d::RigidBody* rigidBody = nullptr;
	rp3d::PhysicsWorld* world = nullptr;
	bool stop = false;
};
#endif