#pragma once
#include <include/raylib-cpp.hpp>

namespace settings
{
	// Window Settings
	inline std::string title = "YOUR NAME HERE"; // Title of the window

	inline int tileSize = 16; // Tile size used to multiply many calculations, in future dynamically change to percentage of screen size
	inline raylib::Vector2 gridSize{50, 28}; // Size of the screen "grid" in tiles
	inline raylib::Vector2 screenSize = gridSize * tileSize; // True screen size

	inline raylib::Color backgroundColour(0x282c34ff); // Background colour, note the required use of 100% opacity

	// Scaling settings
	inline int scaleFactor = 2;
	inline raylib::Vector2 getScaledSize() {
		return screenSize * scaleFactor;
	};
	inline raylib::Vector2 scaleOrigin = {0, 0};

	// Font Settings
	inline raylib::Font defaultFont; // The default raylib text glyphs
	inline raylib::Color textColor = raylib::Color::RayWhite();
}