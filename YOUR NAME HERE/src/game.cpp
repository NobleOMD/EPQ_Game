#include "Game.hpp"

void clampWithin(raylib::Vector2 area, raylib::Vector2 &position, raylib::Vector2 offset)
{
	area -= offset; // Account for the fact that pos is normally calculated from top left

	if (position.x < 0)
	{
		position.x = 0;
	}
	else if (position.y < 0)
	{
		position.y = 0;
	}
	else if (position.x > area.x)
	{
		position.x = area.x;
	}
	else if (position.y > area.y)
	{
		position.y = area.y;
	}
}