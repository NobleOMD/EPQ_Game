#pragma once
#include <include/raylib-cpp.hpp>
#include "ecs/types.hpp"

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

