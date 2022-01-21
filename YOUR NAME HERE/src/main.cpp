#include <include/raylib-cpp.hpp> // Cpp headers that include class functionality

#include "settings.hpp" // My global variables
#include "entities.hpp" // Entities include header

int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	raylib::Window window(settings::screenSize.x, settings::screenSize.y, settings::title);

	window.SetState(FLAG_VSYNC_HINT); // Use V-Sync to autodetect and run at monitor refresh rate

	PlayerCharacter player{ { 1, 2 }, { 25, 15 }, { 128, 68 } }; // Initialise a player with texture
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!window.ShouldClose()) {   // Detect window close button or ESC key
		// Update
		//----------------------------------------------------------------------------------
		player.update();
		if (IsKeyPressed(KEY_F) && window.IsFullscreen())
		{
			// Minimise
		}
		else if (IsKeyPressed(KEY_F) && !window.IsFullscreen())
		{
			// Maximise
		}
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		window.BeginDrawing();
		{
			window.ClearBackground(settings::backgroundColour);
			player.draw();
		}
		window.EndDrawing();
		//----------------------------------------------------------------------------------
	}

	return 0;
}
