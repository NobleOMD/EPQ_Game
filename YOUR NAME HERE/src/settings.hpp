#pragma once
#include <include/raylib-cpp.hpp>

namespace settings
{
	// Window Settings
	inline std::string title = "YOUR NAME HERE"; // Title of the window

	inline constexpr int tileSize = 16; // Tile size used to multiply many calculations, in future dynamically change to percentage of screen size
	inline raylib::Vector2 gridSize{25, 15}; // Size of the screen "grid" in tiles
	inline raylib::Vector2 screenSize = gridSize * tileSize; // True screen size

	inline raylib::Color backgroundColour(0x222222FF); // Background colour, note the required use of 100% opacity

	// Scaling globals
	inline constexpr int defaultScaleFactor = 3;
	inline char scaleFactor = defaultScaleFactor; // Working scale factor
	inline raylib::Vector2 scaleOrigin = {0, 0}; // Origin used by the scaleCanvas

	// Get the current screen size according to the scale factor
	raylib::Vector2 getScaledSize();

	// Font Settings
	inline raylib::Font defaultFont; // The default raylib text glyphs
	inline raylib::Color textColor = raylib::Color::RayWhite();
}