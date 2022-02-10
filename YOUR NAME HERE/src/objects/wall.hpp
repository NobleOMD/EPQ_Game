#pragma once
#include <include/raylib-cpp.hpp>
#include "../settings.hpp"

#include "objectRectangle.hpp"

// Wall: collision at grid position (Complete)
//---------------------------------------------------------------------------------
struct Wall: public ObjectRectangle {
	Wall(raylib::Vector2 gridPos);
};
//---------------------------------------------------------------------------------