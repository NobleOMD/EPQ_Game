#pragma once
#include <random>
#include <include/raylib-cpp.hpp>

#include "settings.hpp"

namespace game
{
	// Return a mt19937 random number seeded using time since game initialised
	inline std::mt19937 random(GetTime() * 1'000'000);
	// Return a mt19937 random number within the range specified
	float mt19937range(float min, float max);

	// Used to clamp a (position) to within an (area), (offset) is used to account for the fact that position is usually calculated from top left
	void clampWithin(raylib::Vector2 area, raylib::Vector2 &position, raylib::Vector2 offset);

	// Maximise and minimise the (window) according to the correct scaling for the monitor being used
	void scaleFullscreen(raylib::Window &window, bool fullscreen);
}
