#include "Game.hpp"

float game::mt19937range(float min, float max) {
	int mod = max * 100.0f;
	return min + (random() % mod) / 100.0f;
}

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

		globals::scaleFactor = globals::defaultScaleFactor;
		globals::scaleOrigin = {0, 0};

		window.SetSize(globals::getScaledSize());
	}
	else if (!fullscreen) {
		raylib::Vector2 monitorSize{(float) GetMonitorWidth(GetCurrentMonitor()), (float) GetMonitorHeight(GetCurrentMonitor())};

		// Maximise
		window.SetFullscreen(true);

		raylib::Vector2 scale = monitorSize / (globals::getScaledSize());
		globals::scaleFactor = std::max(scale.x, scale.y) * globals::scaleFactor; // Scale the image size to match the screen size
		globals::scaleOrigin = (monitorSize - globals::getScaledSize()) / 2;

		window.SetSize(monitorSize);
	}
}