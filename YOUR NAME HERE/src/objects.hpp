#pragma once
#include <include/raylib-cpp.hpp>
#include "ecs/ECSManager.hpp"
#include "systems.hpp"
#include "components.hpp"

namespace createObject
{
	ObjectID Actor(raylib::Vector2 position, raylib::Vector2 size, raylib::Texture *texture, raylib::Rectangle textureRect);
	ObjectID AnimatedActor(raylib::Vector2 position, raylib::Vector2 size, raylib::Texture *texture, raylib::Rectangle textureRect, std::vector<uint8_t> frameOrder, float frameTime);
	ObjectID Player(raylib::Vector2 position, raylib::Vector2 size, raylib::Texture *texture, raylib::Rectangle textureRect, std::vector<uint8_t> frameOrder, float frameTime);
}
