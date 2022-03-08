#pragma once
#include <include/raylib-cpp.hpp>
#include "ecs/types.hpp"

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
	std::vector<uint8_t> frameOrder;
	uint8_t frameIndex = 0;
};

struct Timer {
	ObjectID objectID;
	float timerLength;
	float timeRemaining = timerLength;
};

struct FrameTimer: public Timer {};