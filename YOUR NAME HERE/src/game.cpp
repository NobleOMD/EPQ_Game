#include "Game.hpp"

// Clamp a (position) vector within a specified (area)
void game::clampWithin(raylib::Vector2 area, raylib::Vector2 &position, raylib::Vector2 offset) {
	area -= offset; // Account for the fact that pos is normally calculated from top left

	if (position.x < 0) position.x = 0;
	else if (position.y < 0) position.y = 0;
	else if (position.x > area.x) position.x = area.x;
	else if (position.y > area.y) position.y = area.y;
}

// Set the game (window) to (fullscreen) and set the correct scale factor to match
void game::scaleFullscreen(raylib::Window &window, bool fullscreen) {
	if (fullscreen) {
		// Minimise
		window.SetFullscreen(false);

		settings::scaleFactor = 2;
		settings::scaleOrigin = {0, 0};

		window.SetSize(settings::getScaledSize());
	}
	else if (!fullscreen) {
		raylib::Vector2 monitorSize{(float) GetMonitorWidth(GetCurrentMonitor()), (float) GetMonitorHeight(GetCurrentMonitor())};

		// Maximise
		window.SetFullscreen(true);

		raylib::Vector2 scale = monitorSize / (settings::getScaledSize());
		settings::scaleFactor = std::max(scale.x, scale.y) * settings::scaleFactor; // Scale the image size to match the screen size
		settings::scaleOrigin = (monitorSize - settings::getScaledSize()) / 2;

		window.SetSize(monitorSize);
	}
}