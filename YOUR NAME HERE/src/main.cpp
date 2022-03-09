#include <include/raylib-cpp.hpp> // Cpp headers that include class functionality

#include "../textures/dungeonTileset.h"

#include "settings.hpp" // My global variables
#include "game.hpp"		// General game functions

#include "systems.hpp"
#include "objects.hpp"

int main() {
	// Initialization
	//--------------------------------------------------------------------------------------
	raylib::Window window(settings::getScaledSize().x, settings::getScaledSize().y, settings::title);
	window.SetState(FLAG_VSYNC_HINT); // Use V-Sync to autodetect and run at monitor refresh rate

	registerComponents(); // Register all components to the componentManager
	systems::registerSystems();

	raylib::Texture tileSet(
		raylib::Image(".png", __0x72_DungeonTilesetII_v1_4_png, __0x72_DungeonTilesetII_v1_4_png_len)
	);

	createObject::DamageAnimated(
		raylib::Vector2{12, 7},				// Position
		raylib::Vector2{1, 1},				// Size
		&tileSet,							// Texture
		raylib::Rectangle{16, 176, 16, 16},	// Texture sub-rectangle
		{0, 1, 2, 3},						// Animation frame sequence
		0.075,								// Animation frame duration
		1,									// Damage
		4,									// Penetration
		&systems::player					// Targets
	);

	createObject::Player(
		raylib::Vector2{8, 7},				// Position
		raylib::Vector2{1, 1},				// Size
		&tileSet,							// Texture
		raylib::Rectangle{128, 68, 16, 28},	// Texture sub-rectangle
		{ 0, 1, 2, 3 },						// Animation frame sequence
		0.2,								// Animation frame duration
		100									// Health
	);

	createObject::Enemy(
		raylib::Vector2{16, 6},
		raylib::Vector2{1, 2},
		&tileSet,
		raylib::Rectangle{16, 364, 32, 36},
		{ 0, 1, 2, 3 },
		0.3,
		100
	);

	// Texture that the game is rendered to, this is then scaled to the window size
	raylib::RenderTexture scalerCanvas{(int) settings::screenSize.x, (int) settings::screenSize.y};
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!window.ShouldClose()) { // Detect window close button or ESC key
		// Update
		//----------------------------------------------------------------------------------
		systems::handlePlayerInput();
		systems::handleDamage();
		systems::tickAnimations();
		globalManager.removeObjects();

		// Toggle full screen on F key presseds
		if (IsKeyPressed(KEY_F)) game::scaleFullscreen(window, window.IsFullscreen());
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		// Draw the game the scale canvas 
		scalerCanvas.BeginMode();
		{
			window.ClearBackground(settings::backgroundColour);
			systems::drawTextures();
			systems::drawDebug();
		}
		scalerCanvas.EndMode();

		// Stretch the canvas to the window size
		window.BeginDrawing();
		{
			window.ClearBackground(settings::backgroundColour); // This is the colour of the border around the game

			// This draws the scalerCanvas to scaled up size
			DrawTexturePro(
				scalerCanvas.texture,														// Texture
				raylib::Rectangle(0, 0, settings::screenSize.x, -settings::screenSize.y),	// Source
				raylib::Rectangle(settings::scaleOrigin, settings::getScaledSize()),		// Destination
				raylib::Vector2{0, 0},														// Origin
				0,																			// Rotation
				WHITE																		// Tint
			);
		}
		window.EndDrawing();
		//----------------------------------------------------------------------------------
	}

	return 0;
}
