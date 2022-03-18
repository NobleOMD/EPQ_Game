#include "Game.hpp"

float game::mt19937range(float min, float max) {
	int mod = max * 100.0f;
	return min + ((random() % mod) / 100.0f);
}

// Set the game (window) to (fullscreen) and set the correct scale factor to match
void game::scaleFullscreen(raylib::Window &window, bool fullscreen) {
	if (fullscreen) {
		// Minimise
		window.SetFullscreen(false);

		settings::scaleFactor = settings::defaultScaleFactor;
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

void game::textFromCentre(const std::string &text, int size, raylib::Color colour, raylib::Vector2 offset) {
	raylib::Vector2 textSize = {(float) raylib::MeasureText(text, size), (float) size};
	raylib::Vector2	textPosition = (settings::screenSize / 2) - (textSize / 2) + offset;

	raylib::DrawText(text, textPosition.x, textPosition.y, size, colour);
}