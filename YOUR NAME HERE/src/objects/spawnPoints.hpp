#pragma once
#include <include/raylib-cpp.hpp>
#include "../settings.hpp"

#include "objectRectangle.hpp"

// Spawn Point
//--------------------------------------------------------------------------------------
	// DATA:
	// ------------
	// lock state
	// position
	// entity spawn type
	// ------------

	// FUNCTIONS:
	// ------------
	// spawn entity
	// ------------
class SpawnPoint: public ObjectRectangle {
};
//--------------------------------------------------------------------------------------

// Entrance
//--------------------------------------------------------------------------------------
	// DATA:
	// ------------
	// lock state
	// position
	// ------------

	// FUNCTIONS:
	// ------------
	// load level
	// ------------
class Entrance: SpawnPoint {
};
//--------------------------------------------------------------------------------------

// Exit
//--------------------------------------------------------------------------------------
	// DATA:
	// ------------
	// lock state
	// position
	// next level
	// ------------

	// FUNCTIONS:
	// ------------
	// unlock exit
	// unload level
	// load next level
	// ------------
class Exit: SpawnPoint {
};
//--------------------------------------------------------------------------------------