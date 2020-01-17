#ifndef _LUACOMPONENT_H
#define _LUACOMPONENT_H
#include "Component.h"

extern "C" {
#include "LUA53/lua.h"
#include "LUA53/lauxlib.h"
#include "LUA53/lualib.h"
}
#include <LuaBridge/LuaBridge.h>
#include <LuaBridge/Vector.h>

#ifdef _WIN32
#pragma comment(lib, "liblua53.a")
#endif

class Core;
class Entity;

///This class handles the Lua functionality for the engine.
///
///This class handles all Lua instances and the basic API for running lua scripts on objects.
class LuaComponent : public Component
{
public:
	friend class Entity;
	///This method initializes the Lua state as well as running the script.
	///
	///This method executes the passed in script and enables openLibs.
	///@param _filePath This is the filepath of the script
	void initialise(std::string _filePath);

	///This method handles Lua methods that run at the start.
	///
	///This method executes at the start of the game.
	void onInit() override;
	///This method starts just after onInit.
	///
	///This method starts just after onInit and is useful for player stuff.
	void onBegin() override;
	///This method runs the Lua script every tick.
	///
	///This method executes all scripts that implement onTick every tick.
	void onTick() override;
	///This method runs the lua script to draw objects.
	///
	///This method is currently not implemented, but will be able to draw basic objects.
	void onDisplay() override;

	///This method rotates the object every tick.
	///
	///This method rotates the object every tick with the passed in values.
	void rotator();
	///This method runs a sine motion on an object.
	///
	///This method bobs the object up and down, however currently this script is not functional.
	void sineMotion();

	///This destructor destroys the lua state.
	///
	///This destructor cleans up the lua state and exits.
	~LuaComponent();

private:
	//Handle Lua logic
	lua_State *lState = nullptr;
};

#endif