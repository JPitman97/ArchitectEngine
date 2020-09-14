#include "RigidBodyComponent.h"
#include "TransformComponent.h"
#include "Entity.h"
#include "Core.h"
#include "Scene.h"

RigidBodyComponent::RigidBodyComponent()
{}

void RigidBodyComponent::initialise()
{
	//TransformComponent required to initialise
	auto tc = getEntity()->getComponent<TransformComponent>();
	glm::vec3 pos = tc->getPos();
	glm::vec3 rot = tc->getRot();
	glm::quat myquaternion = glm::quat(glm::vec3(rot.z, rot.y, rot.x));
	rp3d::Vector3 position(pos.x, pos.y, pos.z);
	rp3d::Quaternion orientation = rp3d::Quaternion(myquaternion.x,
													myquaternion.y,
													myquaternion.z,
													1);
	rp3d::Transform transform(position, orientation);
	world = getEntity()->getCore()->getActiveScene()->getPhysicsWorld();
	rigidBody = world->createRigidBody(transform);
}

void RigidBodyComponent::onTick()
{
	auto tc = getEntity()->getComponent<TransformComponent>();
	rp3d::Transform transform = rigidBody->getTransform();
	rp3d::Vector3 position = transform.getPosition();
	rp3d::Quaternion rotation = transform.getOrientation();

	tc->setPos(glm::vec3(position.x, position.y, position.z));
	tc->setRot(glm::vec3(rotation.x, rotation.y, rotation.z));
}

void RigidBodyComponent::setType(RIGIDBODYTYPE _rbType)
{
	switch (_rbType)
	{
	case RigidBodyComponent::STATIC:
		rigidBody->setType(rp3d::BodyType::STATIC);
		break;
	case RigidBodyComponent::KINEMATIC:
		rigidBody->setType(rp3d::BodyType::KINEMATIC);
		break;
	case RigidBodyComponent::DYNAMIC:
		rigidBody->setType(rp3d::BodyType::DYNAMIC);
		break;
	default:
		break;
	}
}

void RigidBodyComponent::addCollider(COLLIDERTYPE _colType, glm::vec3 _size)
{
	auto tc = getEntity()->getComponent<TransformComponent>();
	glm::vec3 pos = tc->getPos();
	glm::vec3 rot = tc->getRot();
	glm::quat myquaternion = glm::quat(glm::vec3(rot.z, rot.y, rot.x));
	rp3d::Vector3 position(pos.x, pos.y, pos.z);
	rp3d::Quaternion orientation = rp3d::Quaternion(myquaternion.x,
													myquaternion.y,
													myquaternion.z,
													1);
	rp3d::Transform transform(position, orientation);

	switch (_colType)
	{
	case RigidBodyComponent::BOX:
		const reactphysics3d::Vector3 halfExtents((_size.x) / 2,
												  (_size.y) / 2,
												  (_size.z) / 2);
		rp3d::BoxShape* boxShape = physicsCommon.createBoxShape(halfExtents);
		rigidBody->addCollider(boxShape, transform);
		if (rigidBody->getType() != rp3d::BodyType::STATIC)
			rigidBody->updateMassPropertiesFromColliders();
		break;
	}
}

RigidBodyComponent::~RigidBodyComponent()
{
}
