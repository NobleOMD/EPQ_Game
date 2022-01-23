#pragma once
#include <include/raylib-cpp.hpp>

#include "settings.hpp"

namespace game
{
	// Used to clamp a (position) to within an (area), (offset) is used to account for the fact that position is usually calculated from top left
	void clampWithin(raylib::Vector2 area, raylib::Vector2 &position, raylib::Vector2 offset);

	// Maximise and minimise the (window) according to the correct scaling for the monitor being used
	void scaleFullscreen(raylib::Window &window, bool fullscreen);
}
