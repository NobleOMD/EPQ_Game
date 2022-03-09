#pragma once
#include <include/raylib-cpp.hpp>
#include "ecs/ECSManager.hpp"
#include "systems.hpp"
#include "components.hpp"

namespace createObject
{
	ObjectID TexturedRectangle(raylib::Vector2 position, raylib::Vector2 size, raylib::Texture *texture, raylib::Rectangle textureRect);
	ObjectID AnimatedTexture(raylib::Vector2 position, raylib::Vector2 size, raylib::Texture *texture, raylib::Rectangle textureRect, std::vector<uint8_t> frameSequence, float frameTime);
	ObjectID Entity(raylib::Vector2 position, raylib::Vector2 size, raylib::Texture *texture, raylib::Rectangle textureRect, std::vector<uint8_t> frameSequence, float frameTime, float health);
	ObjectID Enemy(raylib::Vector2 position, raylib::Vector2 size, raylib::Texture *texture, raylib::Rectangle textureRect, std::vector<uint8_t> frameSequence, float frameTime, float health);
	ObjectID Player(raylib::Vector2 position, raylib::Vector2 size, raylib::Texture *texture, raylib::Rectangle textureRect, std::vector<uint8_t> frameSequence, float frameTime, float health);
	ObjectID Damage(raylib::Vector2 position, raylib::Vector2 size, float damage, uint8_t penetration, Group *targets);
	ObjectID DamageAnimated(raylib::Vector2 position, raylib::Vector2 size, raylib::Texture *texture, raylib::Rectangle textureRect, std::vector<uint8_t> frameSequence, float frameTime, float damage, uint8_t penetration, Group *targets);
}
