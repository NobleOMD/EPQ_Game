#pragma once
#include <include/raylib-cpp.hpp>

#include "settings.hpp"
#include "game.hpp"

// GameObject base class
//---------------------------------------------------------------------------------

class GameObject {
protected:
	// Size / position / grid position

	// Check to see if this object is colliding with any other in given pointer vector
	GameObject *collisionCheck(std::vector<GameObject *> allObjects);

	raylib::Vector2 size; // Size in tiles

	raylib::Vector2 gridPosition; // Position on tile grid
	raylib::Vector2 getObjectPosition(); // Calculate object position from grid position and tile size


	// Colour / texture
	raylib::Rectangle objectRectangle{getObjectPosition(), size * settings::tileSize}; // Rectangle that represents the size and position of the object

	raylib::Color objectColour; // Colour of debug draw functions

	raylib::Texture *objectTexture = nullptr; // Pointer to the texture the gameobject uses for rendering
	raylib::Rectangle textureRect; // Rectangle that represents the shape and size of the object within the texture above
	const raylib::Vector2 textureOffset = -(raylib::Vector2) textureRect.GetSize() + size * settings::tileSize; // Annoying offset to align texture with collision box

public:
	GameObject(raylib::Vector2 size, raylib::Vector2 gridPos, raylib::Texture *texture, raylib::Rectangle textureRect = {0, 0, 0, 0}, raylib::Color colour = BLUE);

	virtual void update(); // Override this function for subclasses

	// Draw
	virtual void draw();

	void drawFilled();
	void drawOutline(int thickness);
	void drawTexture();
};

// Entity derived GameObject class
//---------------------------------------------------------------------------------

// An Entity is a GameObject with movement
class Entity: public GameObject {
public:
	Entity(raylib::Vector2 size, raylib::Vector2 gridPos, raylib::Texture *texture, raylib::Rectangle textureRect = {0, 0, 0, 0});

	void move(raylib::Vector2 translation); // Move on the grid with a vector translation
};

// PlayerCharacter derived Entity class
//---------------------------------------------------------------------------------

class PlayerCharacter: public Entity {
private:
	int xp = 0; // Entity total xp
	int level = 0; // Entity level calculated from xp

public:
	using Entity::Entity; // Use the constructors of Entity which in turn uses those of GameObject

	// Move the character according to player input
	void update();
};

// Enemy derived Entity class
//---------------------------------------------------------------------------------

class Enemy: public Entity {
private:
	const float speed = 1.0f; // Average time in seconds per move
	const float speedRange = 0.3f; // Fluctuation +- range
	float moveTimer = speed; // Current speed

public:
	using Entity::Entity; // Use the constructors of Entity which in turn uses those of GameObject

	// Randomly move the Enemy around the screen using timing offsets to make it look more natural
	void update();
};

// Wall derived GameObject class
//---------------------------------------------------------------------------------

class Wall: public GameObject {
public:
	Wall(raylib::Vector2 gridPos);

	void draw();
};