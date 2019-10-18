#ifndef _RENDERER_H
#define _RENDERER_H
#include "Component.h"

class Renderer : public Component
{
public:

	void onDisplay() override;
};

#endif