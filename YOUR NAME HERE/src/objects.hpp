#pragma once
#include <include/raylib-cpp.hpp>
#include "ecs/ECSManager.hpp"
#include "systems.hpp"
#include "components.hpp"

namespace createObject
{
	void Actor(raylib::Vector2 position, raylib::Vector2 size, raylib::Texture *texture, raylib::Rectangle textureRect);
}
