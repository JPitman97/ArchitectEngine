#pragma once
#include "Component.h"
#include "Camera.h"

class TPCameraComponent : public Component
{
public:
	void initialise();

	void onTick() override;

private:
	std::shared_ptr<Camera> camera;
};

