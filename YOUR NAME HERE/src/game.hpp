#pragma once
#include <include/raylib-cpp.hpp>

// Used to clamp a position within an area
// Offset used to control the amount offset moved by at the bottom and right of the screen (because normally position of an object is calculated from top left)
void clampWithin(raylib::Vector2 area, raylib::Vector2& position, raylib::Vector2 offset);