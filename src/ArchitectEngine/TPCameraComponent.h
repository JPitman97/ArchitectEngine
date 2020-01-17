#pragma once
#include "Component.h"
#include "Camera.h"

///This class handles third person camera views.
///
///This class handles the third person camera, however currently this does not function.
class TPCameraComponent : public Component
{
public:
	///This method stores a Camera instance.
	///
	///This method stores a camera instance for use in methods.
	void initialise();

	///This method sets the camera's position to an offset of the targets location.
	///
	///This method tracks an entity with a supplied offset.
	void onTick() override;

private:
	std::shared_ptr<Camera> camera;
};

