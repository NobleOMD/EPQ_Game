#include "miscFunctions.hpp"

bool functions::updateTimer(Timer& timer) {
	timer.timeRemaining -= GetFrameTime();

	if (timer.timeRemaining >= 0) return false;

	timer.timeRemaining = timer.timerDuration;
	return true;
}

void functions::clampWithin(raylib::Vector2 area, raylib::Vector2& position, raylib::Vector2 offset) {
	area -= offset; // Account for the fact that pos is normally calculated from top left

	if (position.x < 0) position.x = 0;
	else if (position.y < 0) position.y = 0;
	else if (position.x > area.x) position.x = area.x;
	else if (position.y > area.y) position.y = area.y;
}
