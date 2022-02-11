#pragma once
#include <include/raylib-cpp.hpp>
#include "../settings.hpp"
#include "../game.hpp"

class ObjectRectangle;
inline std::vector<ObjectRectangle *> allObjects;
inline std::vector<ObjectRectangle *> collisionObjects;

// ObjectRectangle: base class (Complete)
//---------------------------------------------------------------------------------
struct ObjectRectangle: public raylib::Rectangle {
	ObjectRectangle(raylib::Vector2 size, raylib::Vector2 position);
	virtual void update();
	virtual void draw();

	virtual void debug(); // Draw the outline of the rectangle
	void updatePosition();

	int id;

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