#ifndef _LUACOMPONENT_H
#define _LUACOMPONENT_H
#include "Component.h"


class LuaComponent : public Component
{
public:
	LuaComponent();

	void onTick() override;

private:

};

#endif