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
