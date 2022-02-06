#pragma once
#include <include/raylib-cpp.hpp>

#include "settings.hpp"
#include "game.hpp"

class GameObject;
class CollisionObject;
inline std::vector<GameObject *> allObjects;
inline std::vector<CollisionObject *> collisionObjects;

// GameObject base class
//---------------------------------------------------------------------------------

class GameObject {
protected:
	// Size / position / grid position
	raylib::Vector2 size; // Size in tiles

	raylib::Vector2 gridPosition; // Position on tile grid
	raylib::Vector2 getObjectPosition(); // Calculate object position from grid position and tile size

	// Colour / texture
	raylib::Rectangle objectRectangle{getObjectPosition(), size * settings::tileSize}; // Rectangle that represents the size and position of the object

	raylib::Color objectColour; // Colour of debug draw functions

	raylib::Texture *objectTexture = nullptr; // Pointer to the texture the gameobject uses for rendering
	raylib::Rectangle textureRect; // Rectangle that represents the shape and size of the object within the texture above

public:
	GameObject(raylib::Vector2 size, raylib::Vector2 gridPos, raylib::Texture *texture, raylib::Rectangle textureRect = {0, 0, 0, 0}, raylib::Color colour = BLUE);

	virtual void update(); // Override this function for subclasses

	// Draw
	virtual void draw();

	void drawFilled();
	void drawOutline(int thickness);
	void drawTexture();
};

// CollisionObject derived GameObject class
//---------------------------------------------------------------------------------

class CollisionObject: public GameObject {
public:
	// Check to see if this object is colliding with any other in given pointer vector
	CollisionObject *collisionCheck(std::vector<CollisionObject *> objects);

	CollisionObject(raylib::Vector2 size, raylib::Vector2 gridPos, raylib::Texture *texture, raylib::Rectangle textureRect = {0, 0, 0, 0}, raylib::Color colour = BLUE);
};


// Entity derived CollisionObject class
//---------------------------------------------------------------------------------

// An Entity is a CollisionObject with movement
class Entity: public CollisionObject {
public:
	using CollisionObject::CollisionObject;

	void move(raylib::Vector2 translation); // Move on the grid with a vector translation
};

// PlayerCharacter derived Entity class
//---------------------------------------------------------------------------------

class PlayerCharacter: public Entity {
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

class Wall: public CollisionObject {
public:
	Wall(raylib::Vector2 gridPos);

	void draw();
};

class DamageEntity: public GameObject {
private:
	float damage;
	
protected:
	void move(raylib::Vector2 translation);

public:
	DamageEntity(raylib::Vector2 size, raylib::Vector2 gridPos, raylib::Texture *texture, raylib::Rectangle textureRect = {0, 0, 0, 0});

	void update();
};