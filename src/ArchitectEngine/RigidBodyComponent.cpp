#include "RigidBodyComponent.h"
#include "Entity.h"
#include "Core.h"
#include "Scene.h"

RigidBodyComponent::RigidBodyComponent()
{}

void RigidBodyComponent::Init()
{
	rp3d::Vector3 position(0.0, 0.0, 0.0);
	rp3d::Quaternion orientation = rp3d::Quaternion::identity();
	rp3d::Transform transform(position, orientation);
	world = getEntity()->getCore()->getActiveScene()->getPhysicsWorld();
	rigidBody = world->createRigidBody(transform);
}

RigidBodyComponent::~RigidBodyComponent()
{
}
