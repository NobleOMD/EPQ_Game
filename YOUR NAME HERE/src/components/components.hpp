#pragma once
#include <include/raylib-cpp.hpp>
#include "../ecs/types.hpp"

// Setup all components with the component manager
void registerComponents();

// Components should be data only

struct PositionComponent {
	ObjectID objectID;
	raylib::Vector2 position;
};

struct SizeComponent {
	ObjectID objectID;
	raylib::Vector2 size;
};

struct TextureComponent {
	ObjectID objectID;
	raylib::Texture *texture;
	raylib::Rectangle rectangle;
};

struct AnimationInfo {
	ObjectID objectID;

	float frameZero;
	std::vector<uint8_t> frameSequence;
	float timerLength;

	uint8_t frameIndex = 0;
	float timeRemaining = timerLength;
};

struct HealthComponent {
	ObjectID objectID;
	float health;
};

struct DamageComponent {
	ObjectID objectID;

	float damage;
	Group *targets;

	float timerLength;
	float timeRemaining = 0;
};

struct PenetrationCompeont {
	ObjectID objectID;

	uint8_t penetration;
};