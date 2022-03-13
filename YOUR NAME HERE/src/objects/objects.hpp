#pragma once
#include <include/raylib-cpp.hpp>
#include "../ecs/ECSManager.hpp"
#include "../systems/systems.hpp"
#include "../components/components.hpp"

namespace createObject
{
	ObjectID TexturedRectangle(raylib::Vector2 position, raylib::Vector2 size, raylib::Texture *texture, raylib::Rectangle textureRect);
	ObjectID AnimatedTexture(raylib::Vector2 position, raylib::Vector2 size, raylib::Texture *texture, raylib::Rectangle textureRect, std::vector<uint8_t> frameSequence, float frameTime);
	ObjectID Entity(raylib::Vector2 position, raylib::Vector2 size, raylib::Texture *texture, raylib::Rectangle textureRect, std::vector<uint8_t> frameSequence, float frameTime, float health);
	ObjectID Damage(raylib::Vector2 position, raylib::Vector2 size, float damage, float cooldown, Group *targets);
	ObjectID DamageAnimated(raylib::Vector2 position, raylib::Vector2 size, raylib::Texture *texture, raylib::Rectangle textureRect, std::vector<uint8_t> frameSequence, float frameTime, float damage, float cooldown, Group *targets);
	ObjectID Enemy(raylib::Vector2 position, raylib::Vector2 size, raylib::Texture *texture, raylib::Rectangle textureRect, std::vector<uint8_t> frameSequence, float frameTime, float health, float damage, float cooldown);
	ObjectID Player(raylib::Vector2 position, raylib::Texture *texture);
}
