#pragma once
#include <include/raylib-cpp.hpp>
#include "../settings.hpp"

#include "objectRectangle.hpp"
#include "particle.hpp"

// Attack
//--------------------------------------------------------------------------------------
	// DATA:
	// ------------
	// position
	// shape
	// damage
	// time
	// targets
	// ------------

	// FUNCTIONS:
	// ------------
	// attack
	// ------------
class Attack: public Particle {
};
//--------------------------------------------------------------------------------------

// Damage
//--------------------------------------------------------------------------------------
	// DATA:
	// ------------
	// position
	// damage
	// targets
	// ------------
	// 
	// FUNCTIONS:
	// ------------
	// damage targets
	// ------------
class Damage: public ObjectRectangle {
};
//--------------------------------------------------------------------------------------

