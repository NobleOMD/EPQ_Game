#pragma once
#include <include/raylib-cpp.hpp>

namespace settings
{

	// Window Settings
	inline std::string title = "YOUR NAME HERE"; // Title of the window

	inline int tileSize = 16; // Tile size used to multiply many calculations, in future dynamically change to percentage of screen size
	inline raylib::Vector2 gridSize{ 50, 30 }; // Size of the screen "grid" in tiles
	inline raylib::Vector2 screenSize = gridSize * tileSize; // True screen size
	inline int scaleFactor = 2;

	inline raylib::Color backgroundColour(0x282c34ff); // Background colour, note the required use of 100% opacity

	// Font Settings
	inline raylib::Font defaultFont; // The default raylib text glyphs
	inline raylib::Color textColor = raylib::Color::RayWhite();

}