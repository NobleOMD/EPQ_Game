#pragma once
#include <include/raylib-cpp.hpp>
#include "../ecs/types.hpp"

class MovementSystem: public BaseSystem{
public:
	void update() override {}

	void move(ObjectID objectID, raylib::Vector2 translation);
};