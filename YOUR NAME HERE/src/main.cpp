#include <include/raylib-cpp.hpp> // Cpp headers that include class functionality

#include "../textures/dungeonTileset.h"
#include "settings.hpp" // My global variables
#include "gameObject.hpp" // Entities include header
#include "game.hpp"		// General game functions

int main() {
	// Initialization
	//--------------------------------------------------------------------------------------
	raylib::Window window(settings::getScaledSize().x, settings::getScaledSize().y, settings::title);
	window.SetState(FLAG_VSYNC_HINT); // Use V-Sync to autodetect and run at monitor refresh rate

	raylib::Texture tileSet(
		raylib::Image(".png", __0x72_DungeonTilesetII_v1_4_png, __0x72_DungeonTilesetII_v1_4_png_len)
	);

	// Texture that the game is rendered to, this is then scaled to the window size
	raylib::RenderTexture scalerCanvas{(int) settings::screenSize.x, (int) settings::screenSize.y};

	DamageEntity tile(
		raylib::Vector2{1, 1},				// Size in tiles
		raylib::Vector2{0, 0},				// Position on tilegrid
		&tileSet,							// Address of texture
		raylib::Rectangle{16, 64, 16, 16}	// Rectangle that represents texture area in image
	);
	Wall tile2(
		raylib::Vector2{0, 1}
	);

	PlayerCharacter player(
		raylib::Vector2{1, 1},				// Size in tiles
		raylib::Vector2{25, 15},			// Position on tilegrid
		&tileSet,							// Address of texture
		raylib::Rectangle{128, 68, 16, 28},	// Rectangle that represents texture area in image
		100.0F								// Health
	);

	Enemy zombie(
		raylib::Vector2{1, 2},				// Size in tiles
		raylib::Vector2{10, 3},				// Position on tilegrid
		&tileSet,							// Address of texture
		raylib::Rectangle{16, 270, 32, 34},	// Rectangle that represents texture area in image
		100.0F								// Health
	);
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!window.ShouldClose()) { // Detect window close button or ESC key
		// Update
		//----------------------------------------------------------------------------------
		for (GameObject *object : allObjects) {
			object->update();
		}

		// Toggle full screen on F key pressed
		if (IsKeyPressed(KEY_F)) game::scaleFullscreen(window, window.IsFullscreen());
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		// Draw the game the scale canvas 
		scalerCanvas.BeginMode();
		{
			window.ClearBackground(settings::backgroundColour);
			for (GameObject *object : allObjects) {
				object->draw();
				//object->drawOutline(1); // Used to debug collision boxes
			}
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
