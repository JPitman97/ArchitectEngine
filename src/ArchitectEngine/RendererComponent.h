#ifndef _RENDERERCOMPONENT_H
#define _RENDERERCOMPONENT_H
#include "Component.h"

class RendererComponent : public Component
{
public:

	void onDisplay() override;
};

#endif