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

	raylib::Texture tileSet(
		raylib::Image(".png", __0x72_DungeonTilesetII_v1_4_png, __0x72_DungeonTilesetII_v1_4_png_len)
	);

	createObject::Player(
		raylib::Vector2{8, 7},
		raylib::Vector2{1, 1},
		&tileSet,
		raylib::Rectangle{128, 68, 16, 28},
		{ 0, 1, 2, 3 },
		0.3
	);

	createObject::AnimatedActor(
		raylib::Vector2{16, 6},
		raylib::Vector2{2, 2},
		&tileSet,
		raylib::Rectangle{16, 364, 32, 36},
		{ 0, 1, 2, 3 },
		0.4
	);

	// Texture that the game is rendered to, this is then scaled to the window size
	raylib::RenderTexture scalerCanvas{(int) settings::screenSize.x, (int) settings::screenSize.y};
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!window.ShouldClose()) { // Detect window close button or ESC key
		// Update
		//----------------------------------------------------------------------------------
		// Toggle full screen on F key presseds
		systems::handlePlayerInput();
		systems::tickAnimations();
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
