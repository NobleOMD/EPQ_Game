#include <include/raylib-cpp.hpp> // Cpp headers that include class functionality

#include "settings.hpp" // My global variables
#include "entities.hpp" // Entities include header

int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	raylib::Window window(
		settings::screenSize.x * settings::scaleFactor,
		settings::screenSize.y * settings::scaleFactor,
		settings::title
	);

	window.SetState(FLAG_VSYNC_HINT); // Use V-Sync to autodetect and run at monitor refresh rate

	raylib::RenderTexture2D scalerCanvas{(int) settings::screenSize.x, (int) settings::screenSize.y};
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
				raylib::Rectangle({0, 0}, settings::screenSize * settings::scaleFactor),	// Destination
				raylib::Vector2(0, 0),														// Origin
				0,																			// Rotation
				WHITE																		// Tint
			);
		}
		window.EndDrawing();
		//----------------------------------------------------------------------------------
	}

	return 0;
}
