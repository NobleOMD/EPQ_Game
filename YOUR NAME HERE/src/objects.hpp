#pragma once
#include <include/raylib-cpp.hpp>

#include "settings.hpp"
#include "game.hpp"

// ObjectRectangle: base class
//---------------------------------------------------------------------------------
class ObjectRectangle: public raylib::Rectangle {
public:
	ObjectRectangle(raylib::Vector2 size, raylib::Vector2 position);
	virtual void update(); // Update object position from grid position and tile size
	virtual void draw();

	virtual void debug(); // Draw the outline of the rectangle

protected:
	// Size / position / grid position
	raylib::Vector2 size; // Size in tiles
	raylib::Vector2 position; // Position on tile grid
};

inline std::vector<ObjectRectangle *> allObjects;
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


// Collision: adds collision to ObjectRectangle
//---------------------------------------------------------------------------------
class Collision: public ObjectRectangle {
public:
	Collision(raylib::Vector2 size, raylib::Vector2 position);
	Collision *collisionCheck(std::vector<Collision *> objects);
};

inline std::vector<Collision *> collisionObjects;
//---------------------------------------------------------------------------------


// Movement: adds movement to ObjectRectangle
//---------------------------------------------------------------------------------
class Movement: public ObjectRectangle {
public:
	using ObjectRectangle::ObjectRectangle;
	void move(raylib::Vector2 translation); // Move on the tile grid using vector translation
};
//---------------------------------------------------------------------------------



// Entity: combines Textures, Collision and Movement
//---------------------------------------------------------------------------------
class Entity: public ObjectRectangle, public ObjectTexture, public Movement, public Collision{
public:
	Entity(raylib::Vector2 size, raylib::Vector2 position, raylib::Texture *texture, raylib::Rectangle textureRect);
	void move(raylib::Vector2 translation); // Move, checking for collision
};
//---------------------------------------------------------------------------------


// PlayerCharacter: derived from Entity
//---------------------------------------------------------------------------------
class PlayerCharacter: public Entity{
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
class Wall: public Collision {
public:
	Wall(raylib::Vector2 gridPos);
};
//---------------------------------------------------------------------------------

