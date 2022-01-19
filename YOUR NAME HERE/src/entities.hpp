#pragma once
#include <include/raylib-cpp.hpp>

#include "settings.hpp"
#include "game.hpp"

// Entity parent class
//---------------------------------------------------------------------------------
class Entity {
private:
	// Size, position, grid position, colour/texture
	raylib::Vector2 size; // Entity is one tile wide and one high

	raylib::Vector2 gridPosition; // Initial starting position of player at 1, 1
	raylib::Vector2 getPosition();

	raylib::Rectangle rectangle{ getPosition(), size * settings::tileSize }; // The rectange the player is represented as
	raylib::Color entityColour = BLUE;

public:
	Entity(raylib::Vector2 size, raylib::Vector2 gridPos, raylib::Color colour);

	// Move
	void move(raylib::Vector2 translation);

	// Draw
	void draw();
	void drawOutline(int thickness);
};

// Player child class
//---------------------------------------------------------------------------------
class Player : public Entity {
private:

public:
	Player(raylib::Vector2 size, raylib::Vector2 gridPos, raylib::Color colour);

	// Player keyboard input to move
	void move();
};