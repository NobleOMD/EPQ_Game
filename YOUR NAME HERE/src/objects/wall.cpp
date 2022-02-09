#include "wall.hpp"

// Wall: collision at grid position
//---------------------------------------------------------------------------------
Wall::Wall(raylib::Vector2 gridPos)
	:
	ObjectRectangle({1, 1}, gridPos) {
	collisionObjects.push_back(this);
}