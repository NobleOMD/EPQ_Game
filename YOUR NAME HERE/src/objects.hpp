#pragma once
#include <include/raylib-cpp.hpp>

#include "settings.hpp"
#include "game.hpp"

class ObjectRectangle;
inline std::vector<ObjectRectangle *> allObjects;
inline std::vector<ObjectRectangle *> collisionObjects;


// ObjectRectangle: base class
//---------------------------------------------------------------------------------
struct ObjectRectangle: public raylib::Rectangle {
	ObjectRectangle(raylib::Vector2 size, raylib::Vector2 position);
	virtual void update(); // Update object position from grid position and tile size
	virtual void draw();

	virtual void debug(); // Draw the outline of the rectangle
	void updatePosition();

	// Size / position / grid position
	raylib::Vector2 size; // Size in tiles
	raylib::Vector2 position; // Position on tile grid
};
//---------------------------------------------------------------------------------


// Collision: adds collision to ObjectRectangle
//---------------------------------------------------------------------------------
ObjectRectangle *collisionCheck(ObjectRectangle *target, std::vector<ObjectRectangle *> objects);
//---------------------------------------------------------------------------------


// Movement: adds movement to ObjectRectangle
//---------------------------------------------------------------------------------
void movement(ObjectRectangle *target, raylib::Vector2 translation); // Move on the tile grid using vector translation
//---------------------------------------------------------------------------------


// ObjectTexture: ObjectRectangle drawn with texture
//---------------------------------------------------------------------------------
class ObjectTexture: public ObjectRectangle {
public:
	ObjectTexture(raylib::Vector2 size, raylib::Vector2 position, raylib::Texture *texture, raylib::Rectangle textureRect);
	void draw();

protected:
	// Colour / texture
	raylib::Texture *objectTexture; // Pointer to the texture the gameobject uses for rendering
	raylib::Rectangle textureRect; // Rectangle that represents the shape and size of the object within the texture above
};
//---------------------------------------------------------------------------------


// Entity: combines Textures, Collision and Movement
//---------------------------------------------------------------------------------
class Entity: public ObjectTexture {
public:
	Entity(raylib::Vector2 size, raylib::Vector2 position, raylib::Texture *texture, raylib::Rectangle textureRect);
	void move(raylib::Vector2 translation); // Move, checking for collision
};
//---------------------------------------------------------------------------------


// PlayerCharacter: derived from Entity
//---------------------------------------------------------------------------------
class PlayerCharacter: public Entity {
public:
	using Entity::Entity;
	void update(); // Move according to player input
};
//---------------------------------------------------------------------------------


// Enemy: derived from Entity
//---------------------------------------------------------------------------------
class Enemy: public Entity {
public:
	Enemy(raylib::Vector2 size, raylib::Vector2 position, raylib::Texture *texture, raylib::Rectangle textureRect);
	void update();

private:
	const float speed = 1.0f; // Average time in seconds per move
	const float speedRange = 0.3f; // Fluctuation +- range
	float moveTimer = speed; // Current speed
};

inline std::vector<Enemy *> enemyObjects;
//---------------------------------------------------------------------------------


// Wall: collision at grid position
//---------------------------------------------------------------------------------
class Wall: public ObjectRectangle {
public:
	Wall(raylib::Vector2 gridPos);
};
//---------------------------------------------------------------------------------

