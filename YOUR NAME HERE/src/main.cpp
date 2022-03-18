#include <include/raylib-cpp.hpp> // Cpp headers that include class functionality

#include "settings.hpp" // My global variables
#include "game.hpp"		// General game functions
#include "systems/systems.hpp"
#include "objects/objects.hpp"

int main() {
	// Initialization
	//--------------------------------------------------------------------------------------
	raylib::Window window(settings::getScaledSize().x, settings::getScaledSize().y, settings::title);
	window.SetState(FLAG_VSYNC_HINT); // Use V-Sync to autodetect and run at monitor refresh rate

	components::registerComponents(); // Register all components with the componentManager
	systems::registerSystems(); // Register all system groups with the systemManager

	raylib::Texture tileSet("textures\\0x72_DungeonTilesetII_v1.4.png");
	raylib::Texture background("textures\\background.png");

	// Initialise game objects
	//----------------------------------------------------------------------------------
	createObject::Wall({0, 0}, {2, settings::gridSize.y});
	createObject::Wall({settings::gridSize.x - 2, 0}, {2, settings::gridSize.y});
	createObject::Wall({0, 0}, {settings::gridSize.x, 1});
	createObject::Wall({0, settings::gridSize.y - 1}, {settings::gridSize.x, 1});

	createObject::Spikes(
		raylib::Vector2{12, 7},						// Position
		&tileSet,									// Texture
		globalManager.getSystemGroup<PlayerInput>()	// Targets
	);

	createObject::Player(
		raylib::Vector2{8, 7},
		&tileSet
	);

	createObject::BigDemon(
		raylib::Vector2{16, 6},
		&tileSet
	);
	//----------------------------------------------------------------------------------

	// Texture that the game is rendered to, this is then scaled to the window size
	raylib::RenderTexture scalerCanvas{(int) settings::screenSize.x, (int) settings::screenSize.y};
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!window.ShouldClose()) { // Detect window close button or ESC key
		// Update
		//----------------------------------------------------------------------------------
		systems::updateSystems();
		globalManager.removeObjects();

		// Toggle full screen on F key pressed
		if (IsKeyPressed(KEY_F)) game::scaleFullscreen(window, window.IsFullscreen());
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		// Draw the game the scale canvas 
		scalerCanvas.BeginMode();
		{
			//window.ClearBackground(settings::backgroundColour);

			DrawTexture(background, 0, 0, WHITE);
			systems::drawSystems();

			if (game::over) {
				game::textFromCentre("Game Over", 30, RED, {0, -5});
				game::textFromCentre("Press ESC to leave the game.", 5, RED, {0, 10});
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
