#pragma once
#include <include/raylib-cpp.hpp>
#include "../ecs/types.hpp"

class MovementSystem: public SystemGroup {
public:
	void move(ObjectID objectID, raylib::Vector2 translation);
};