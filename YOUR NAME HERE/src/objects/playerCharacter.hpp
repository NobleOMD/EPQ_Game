#pragma once
#include <include/raylib-cpp.hpp>
#include "../settings.hpp"

#include "entity.hpp"
#include "item.hpp"

// PlayerCharacter: derived from Entity
//---------------------------------------------------------------------------------
	// DATA:
	// ------------
	// xp
	// level
	// health
	// position
	// size
	// texture
	// current item
	// inventory
	//		items

	// FUNCTIONS:
	// ------------
	// movement
	// input
	//		show inventory
	//		move
	//		attack
	// 
	// collision
	//		damage
	//		xp
	//		stop at walls and other entites
class PlayerCharacter: public Entity {
public:
	using Entity::Entity;
	void update(); // Move according to player input
};
//---------------------------------------------------------------------------------
