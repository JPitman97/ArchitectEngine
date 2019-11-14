#pragma once
#include "Component.h"
#include "Camera.h"

class CameraComponent : public Component
{
public:
	CameraComponent();
	~CameraComponent();

	void Tick(float _DT) const;

	void initialise();
private:
	std::shared_ptr<Camera> camera;
};

