#pragma once
#include <include/raylib-cpp.hpp>
#include "../settings.hpp"

#include "objectRectangle.hpp"

// Wall: collision at grid position (Complete)
//---------------------------------------------------------------------------------
class Wall: public ObjectRectangle {
public:
	Wall(raylib::Vector2 gridPos);
};
//---------------------------------------------------------------------------------