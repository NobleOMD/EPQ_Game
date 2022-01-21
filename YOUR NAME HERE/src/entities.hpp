#pragma once
#include <include/raylib-cpp.hpp>

#include "settings.hpp"
#include "game.hpp"

// Entity parent class
//---------------------------------------------------------------------------------
class Entity
{
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
	void drawFilled();
	void drawOutline(int thickness);
};

// PlayerCharacter child class
//---------------------------------------------------------------------------------
class PlayerCharacter: public Entity
{
private:
	int outlineSize = 3;

	float health = 100.0f;
	int xp = 0;
	int level = 0;

	void playerInput(); // Player keyboard input to move / make an action

public:
	PlayerCharacter(raylib::Vector2 size, raylib::Vector2 gridPos, raylib::Color colour);

	int state = 0;

	void update(); // Return a value depending on state
	void draw();
};