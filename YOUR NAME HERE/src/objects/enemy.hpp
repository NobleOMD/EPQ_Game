#pragma once
#include <include/raylib-cpp.hpp>
#include "../settings.hpp"

#include "entity.hpp"
#include "item.hpp"

// Enemy: derived from Entity
//---------------------------------------------------------------------------------
	// DATA:
	// ------------
	// difficulty
	// xp dropped
	// health
	// position
	// size
	// texture
	// current item
	// item drops

	// FUNCTIONS:
	// ------------
	// movement
	//		AI
	//		movement
	//			swarming
	//			not getting stuck
	//			path finding
	//		timing attacks
	// 
	// collision
	//		damage other entities
	//		stop at walls and other entities
class Enemy: public Entity {
public:
	Enemy(raylib::Vector2 size, raylib::Vector2 position, raylib::Texture *texture, raylib::Rectangle textureRect, float health);
	void update();

private:
	const float speed = 1.0f; // Average time in seconds per move
	const float speedRange = 0.3f; // Fluctuation +- range
	float moveTimer = speed; // Current speed
};

inline std::vector<Enemy *> enemyObjects;
//---------------------------------------------------------------------------------
