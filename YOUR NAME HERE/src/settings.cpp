#include "settings.hpp"

// Get the current screen size according to the scale factor
raylib::Vector2 settings::getScaledSize() {
	return screenSize * scaleFactor;
}
