#pragma once
#include <random>
#include <include/raylib-cpp.hpp>

#include "settings.hpp"

namespace game
{
	inline bool over = false;

	// Return a mt19937 random number seeded using time since game initialised
	inline std::mt19937 random(GetTime() * 1'000'000);
	// Return a mt19937 random number within the range specified
	float mt19937range(float min, float max);

	// Collision
	// Used to clamp a (position) to within an (area), (offset) is used to account for the fact that position is usually calculated from top left
	void clampWithin(raylib::Vector2 area, raylib::Vector2 &position, raylib::Vector2 offset = {0, 0});

	// Maximise and minimise the (window) according to the correct scaling for the monitor being used
	void scaleFullscreen(raylib::Window &window, bool fullscreen);

	void textFromCentre(const std::string &text, int size, raylib::Color colour, raylib::Vector2 offset = {0, 0});
}

// User Interface
//--------------------------------------------------------------------------------------
// DATA:
// ------------
// HUD
//		health
//		XP
//		current item
//		character mugshot
// 
// Inventory
//		player items
//		selected item
//			item damage/defense
//			item name
//			item description
//  
// Skill Tree
//		skills available
//		selected item
//			item name
//			item description
// Level
//		Name
//		Wave number
//		Wave progression
// 
// Main menu
//		Level selected
//		Levels completed
// ------------
// 
// FUNCTIONS:
// ------------
// Display item icon
// Display item scaled up
// 
// Select grid position
// 
// Exit screen state
// 69
// 420
// :)
// ------------
//--------------------------------------------------------------------------------------

// Level
//--------------------------------------------------------------------------------------
// DATA:
// ------------
// Name
// Position in world
// Entrance
// Texture
// Collision areas
// Current wave number
// Waves
// Chest position
// Exit(s)
// ------------
// 
// FUNCTIONS:
// ------------
// Initialise level
// Spawn wave
// Generate chest
// Destroy level
// ------------
//--------------------------------------------------------------------------------------

// Wave
//--------------------------------------------------------------------------------------
// DATA:
// ------------
// Wave number
// Enemy spawning positions
// ------------
// 
// FUNCTIONS:
// ------------
// Spawn enemies
// ------------
//--------------------------------------------------------------------------------------
