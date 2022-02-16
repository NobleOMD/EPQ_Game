#include <include/raylib-cpp.hpp> // Cpp headers that include class functionality

#include "../textures/dungeonTileset.h"
#include "settings.hpp" // My global variables
#include "container.hpp"
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
	//--------------------------------------------------------------------------------------

	for (int i = 0; i < 5; i++) {
		addBlob(createdObjects, EnemyObject({1, 2}, {5, 7}, &tileSet, {16, 270, 32, 34}));
		std::unordered_map<unsigned int, Object *> objects = blobContainer<Object *>[typeid(Object *)];
	}

	// Main game loop
	while (!window.ShouldClose()) { // Detect window close button or ESC key
		// Update
		//----------------------------------------------------------------------------------
		std::unordered_map<unsigned int, Object *> objects = blobContainer<Object *>[typeid(Object *)];
		for (const std::pair<unsigned int, Object *> &pair : objects) {
			pair.second->update();
		}

		EnemyObject rect = getBlob<EnemyObject>(3);
		// Toggle full screen on F key pressed
		if (IsKeyPressed(KEY_F)) game::scaleFullscreen(window, window.IsFullscreen());
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		// Draw the game the scale canvas 
		scalerCanvas.BeginMode();
		{
			window.ClearBackground(settings::backgroundColour);
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
