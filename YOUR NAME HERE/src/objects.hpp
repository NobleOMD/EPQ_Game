#pragma once
#include <include/raylib-cpp.hpp>

#include "settings.hpp"
#include "game.hpp"

class ObjectRectangle;
inline std::vector<ObjectRectangle *> allObjects;
inline std::vector<ObjectRectangle *> collisionObjects;


// ObjectRectangle: base class
//---------------------------------------------------------------------------------
	// DATA:
	// ------------
	// position
	// size
	// ------------

	// FUNCTIONS:
	// ------------
	// draw
	// ------------
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
	// DATA:
	// ------------
	// position
	// size
	// texture
	// ------------

	// FUNCTIONS:
	// ------------
	// draw
	// ------------
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
public:
	Entity(raylib::Vector2 size, raylib::Vector2 position, raylib::Texture *texture, raylib::Rectangle textureRect);
	void move(raylib::Vector2 translation); // Move, checking for collision
};
//---------------------------------------------------------------------------------


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
	// DATA:
	// ------------
	// Position
	// ------------

	// FUNCTIONS:
	// ------------
	// ------------
class Wall: public ObjectRectangle {
public:
	Wall(raylib::Vector2 gridPos);
};
//---------------------------------------------------------------------------------

// Chest
//--------------------------------------------------------------------------------------
class Chest: public ObjectTexture {
	// DATA:
	// ------------
	// Item drops
	// Lock state
	// ------------

	// FUNCTIONS:
	// ------------
	// Open chest
	//		drop all items
	// ------------
};
//--------------------------------------------------------------------------------------

// Spawn Point
//--------------------------------------------------------------------------------------
	// DATA:
	// ------------
	// lock state
	// position
	// entity spawn type
	// ------------

	// FUNCTIONS:
	// ------------
	// spawn entity
	// ------------
class SpawnPoint: public ObjectRectangle {
};
//--------------------------------------------------------------------------------------

// Entrance
//--------------------------------------------------------------------------------------
	// DATA:
	// ------------
	// lock state
	// position
	// ------------

	// FUNCTIONS:
	// ------------
	// load level
	// ------------
class Entrance: SpawnPoint {
};
//--------------------------------------------------------------------------------------

// Exit
//--------------------------------------------------------------------------------------
	// DATA:
	// ------------
	// lock state
	// position
	// next level
	// ------------

	// FUNCTIONS:
	// ------------
	// unlock exit
	// unload level
	// load next level
	// ------------
class Exit: SpawnPoint {
};
//--------------------------------------------------------------------------------------

// Item
//--------------------------------------------------------------------------------------
	// DATA:
	// ------------
	// item damage/defense
	// item name
	// item description
	// ------------

	// FUNCTIONS:
	// ------------
	// use item
	// consume item
	// drop item
	// ------------
class Item: public ObjectTexture {
};
//--------------------------------------------------------------------------------------

// Particle
//--------------------------------------------------------------------------------------
	// DATA:
	// ------------
	// position
	// lifetime
	// time existed
	// texture
	// size
	// ------------
	// 
	// FUNCTIONS:
	// ------------
	// move
	// destroy
	// collide
	// ------------

class Particle: public ObjectTexture {
};
//--------------------------------------------------------------------------------------


// Attack
//--------------------------------------------------------------------------------------
	// DATA:
	// ------------
	// position
	// shape
	// damage
	// time
	// targets
	// ------------

	// FUNCTIONS:
	// ------------
	// attack
	// ------------
class Attack: public Particle {
};
//--------------------------------------------------------------------------------------

// Damage
//--------------------------------------------------------------------------------------
	// DATA:
	// ------------
	// position
	// damage
	// targets
	// ------------
	// 
	// FUNCTIONS:
	// ------------
	// damage targets
	// ------------
class Damage: public ObjectRectangle {
};
//--------------------------------------------------------------------------------------