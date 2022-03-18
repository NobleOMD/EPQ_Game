#pragma once
#include <include/raylib-cpp.hpp>
#include "../ecs/types.hpp"

namespace components {
	/// Setup all components with the component manager
	void registerComponents();
}

// Components should be data only

struct Timer: public BaseComponent {
	float timerDuration;
	float timeRemaining;
};

struct PositionComponent: public BaseComponent {
	raylib::Vector2 position;
};

struct SizeComponent: public BaseComponent {
	raylib::Vector2 size;
};

struct TextureComponent: public BaseComponent {
	raylib::Texture *texture;
	raylib::Rectangle rectangle;
};

struct AnimationInfo: public BaseComponent {
	float frameZero;
	std::vector<uint8_t> frameSequence;
	uint8_t frameIndex = 0;
};

struct AnimationTimer: public Timer {};

struct HealthComponent: public BaseComponent {
	float health;
};

struct DamageComponent: public BaseComponent {
	float damage;
	Group *targets;

	float timerLength;
	float timeRemaining = 0;
};

struct DamageTimer: public Timer {};

struct PenetrationCompeont: public BaseComponent {
	uint8_t penetration;
};

struct Movement: public BaseComponent {
	raylib::Vector2 translation;
};