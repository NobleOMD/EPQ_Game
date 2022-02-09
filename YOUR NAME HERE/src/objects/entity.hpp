#pragma once
#include <include/raylib-cpp.hpp>
#include "../settings.hpp"

#include "objectTexture.hpp"
#include "item.hpp"

// Entity: combines Textures, Collision and Movement
//---------------------------------------------------------------------------------
	// DATA:
	// ------------
	// health
	// position
	// size
	// texture
	// current item
	// ------------

	// FUNCTIONS:
	// ------------
	// use item
	// move
	// draw
	// ------------
class Entity: public ObjectTexture {
protected:
	float health = 100;
	Item *currentItem = nullptr;

public:
	Entity(raylib::Vector2 size, raylib::Vector2 position, raylib::Texture *texture, raylib::Rectangle textureRect);
	void move(raylib::Vector2 translation); // Move, checking for collision
};
//---------------------------------------------------------------------------------
