#pragma once
#include "include/raylib-cpp.hpp"
#include "../components/components.hpp"

namespace functions
{
	/// Update the timer
	bool updateTimer(Timer &timer);

	/// Used to clamp a (position) to within an (area), (offset) is used to account for the fact that position is usually calculated from top left
	void clampWithin(raylib::Vector2 area, raylib::Vector2 &position, raylib::Vector2 offset = {0, 0});

}