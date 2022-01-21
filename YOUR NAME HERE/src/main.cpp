#include <include/raylib-cpp.hpp> // Cpp headers that include class functionality

#include "settings.hpp" // My global variables
#include "entities.hpp" // Entities include header
#include "game.hpp"		// General game functions

int main() {
	// Initialization
	//--------------------------------------------------------------------------------------
	int &R_scaleFactor = settings::scaleFactor;
	raylib::Vector2 &R_scaleOrigin = settings::scaleOrigin;

	raylib::Window window(settings::getScaledSize().x, settings::getScaledSize().y, settings::title);
	window.SetState(FLAG_VSYNC_HINT); // Use V-Sync to autodetect and run at monitor refresh rate

	raylib::RenderTexture scalerCanvas{(int) settings::screenSize.x, (int) settings::screenSize.y};
	PlayerCharacter player{{1, 2}, {25, 15}, {128, 68}}; // Initialise a player with texture
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!window.ShouldClose()) { // Detect window close button or ESC key
		// Update
		//----------------------------------------------------------------------------------
		player.update();

		// Toggle full screen on F key pressed
		if (IsKeyPressed(KEY_F)) { game::setFullscreen(window, (window.IsFullscreen())); };
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		scalerCanvas.BeginMode();
		{
			window.ClearBackground(settings::backgroundColour);
			player.draw();
		}
		scalerCanvas.EndMode();

		window.BeginDrawing();
		{
			window.ClearBackground(WHITE);
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
