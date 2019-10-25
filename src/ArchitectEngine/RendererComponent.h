#ifndef _RENDERERCOMPONENT_H
#define _RENDERERCOMPONENT_H
#include "Component.h"


class RendererComponent : public Component
{
public:
	RendererComponent();

	void onDisplay() override;

private:
	unsigned int programId;
	unsigned int vaoId;
};

#endif