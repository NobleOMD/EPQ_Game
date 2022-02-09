#pragma once
#include <include/raylib-cpp.hpp>
#include "../settings.hpp"

#include "objectTexture.hpp"
#include "item.hpp"

// Entity: combines Textures, Collision and Movement
//---------------------------------------------------------------------------------
	// DATA:
	// ------------
	// position
	// size
	// texture
	// health
	// current item
	// ------------

	// FUNCTIONS:
	// ------------
	// use item
	// move
	// draw
	// ------------
class Entity: public ObjectTexture {
public:
	Entity(raylib::Vector2 size, raylib::Vector2 position, raylib::Texture *texture, raylib::Rectangle textureRect, float health);
	Entity(ObjectTexture objectTexture, float health);

	void move(raylib::Vector2 translation); // Move, checking for collision

	float health;

protected:
	Item *currentItem = nullptr;
};

inline std::vector<Entity *> damageableObjects;
//---------------------------------------------------------------------------------
