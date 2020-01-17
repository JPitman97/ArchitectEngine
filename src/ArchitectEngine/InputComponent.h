#ifndef _INPUTCOMPONENT_H
#define  _INPUTCOMPONENT_H

#include "Component.h"

///This class handles inputs.
///
///This class handles inputs from the Input class, and wraps them for ease of use.
class InputComponent : public Component
{
	///This method checks each frame if a WASD key was pressed.
	///
	///This method checks to see if a WASD key was pressed, then sets the position of the object.
	void onTick() override;

};

#endif
