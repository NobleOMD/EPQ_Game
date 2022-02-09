#pragma once
#include <include/raylib-cpp.hpp>
#include "../settings.hpp"

#include "objectRectangle.hpp"
#include "entity.hpp"
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
public:
	Damage(raylib::Vector2 size, raylib::Vector2 position, float damage);

	void update();
private:
	float damage;
};
//--------------------------------------------------------------------------------------

