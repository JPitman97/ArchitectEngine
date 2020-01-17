#include "LuaComponent.h"
#include "Entity.h"
#include "Core.h"
#include "Input.h"
#include "TransformComponent.h"
#include "Time.h"


void LuaComponent::initialise(const std::string _filePath)
{
	lState = luaL_newstate();
	luaL_dofile(lState, _filePath.c_str());
	luaL_openlibs(lState);
	onInit();
	onBegin();
}

void LuaComponent::onInit()
{
	lua_pcall(lState, 0, LUA_MULTRET, 0);
	luabridge::LuaRef onInit = luabridge::getGlobal(lState, "onInit");
	try
	{
		std::string str = onInit();
		std::cout << str << std::endl;
	}
	catch (...)
	{
	}
}

void LuaComponent::onBegin()
{
	lua_pcall(lState, 0, LUA_MULTRET, 0);
	luabridge::LuaRef onBegin = luabridge::getGlobal(lState, "onBegin");
}

void LuaComponent::onTick()
{
	lua_pcall(lState, 0, LUA_MULTRET, 0);
	luabridge::LuaRef onTick = luabridge::getGlobal(lState, "onTick");

	try
	{
		rotator();
		sineMotion();
	}
	catch (...)
	{
	}
}

void LuaComponent::onDisplay()
{
	lua_pcall(lState, 0, LUA_MULTRET, 0);
	luabridge::LuaRef onDisplay = luabridge::getGlobal(lState, "onDisplay");
}

void LuaComponent::rotator()
{
	luabridge::LuaRef rotator = luabridge::getGlobal(lState, "rotator");
	glm::vec3 rot = getEntity()->getComponent<TransformComponent>()->getRot();
	std::vector<float> vecs = rotator(rot.x, rot.y, rot.z);
	getEntity()->getComponent<TransformComponent>()->setRot(glm::vec3(vecs[0], vecs[1], vecs[2]));
}

void LuaComponent::sineMotion()
{
	luabridge::LuaRef sineMotion = luabridge::getGlobal(lState, "sineMotion");
	glm::vec3 pos = getEntity()->getComponent<TransformComponent>()->getPos();
	std::vector<float> vecs = sineMotion(pos.x, pos.y, pos.z, Time::deltaTime);
	getEntity()->getComponent<TransformComponent>()->setPos(glm::vec3(vecs[0], vecs[1], vecs[2]));
}

LuaComponent::~LuaComponent()
{
	if (lState != nullptr)
	{
		lua_close(lState);
		lState = nullptr;
	}
}
