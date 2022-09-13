#pragma once
#include <include/raylib-cpp.hpp>

#include "../ecs/ECSManager.hpp"

namespace createObject
{
	ObjectID TexturedRectangle(raylib::Vector2 position, raylib::Vector2 size, raylib::Texture *texture, raylib::Rectangle textureRect);
	ObjectID AnimatedTexture(raylib::Vector2 position, raylib::Vector2 size, raylib::Texture *texture, raylib::Rectangle textureRect, std::vector<uint8_t> frameSequence, float frameTime);
	ObjectID Damage(raylib::Vector2 position, raylib::Vector2 size, float damage, float cooldown, Group *targets);
	ObjectID DamageAnimated(raylib::Vector2 position, raylib::Vector2 size, raylib::Texture *texture, raylib::Rectangle textureRect, std::vector<uint8_t> frameSequence, float frameTime, float damage, float cooldown, Group *targets);
	ObjectID Entity(raylib::Vector2 position, raylib::Vector2 size, raylib::Texture *texture, raylib::Rectangle textureRect, std::vector<uint8_t> frameSequence, float frameTime, float health);
	ObjectID Enemy(raylib::Vector2 position, raylib::Vector2 size, raylib::Texture *texture, raylib::Rectangle textureRect, std::vector<uint8_t> frameSequence, float frameTime, float health, float damage, float cooldown);
	
	ObjectID Player(raylib::Vector2 position, raylib::Texture *texture);
	ObjectID Wall(raylib::Vector2 position, raylib::Vector2 size = {1, 1});
	ObjectID Spikes(raylib::Vector2 position, raylib::Texture *texture, Group *targets);
	ObjectID BigDemon(raylib::Vector2 position, raylib::Texture *texture);
	ObjectID FireBall(raylib::Vector2 position, raylib::Texture *texture);
}
