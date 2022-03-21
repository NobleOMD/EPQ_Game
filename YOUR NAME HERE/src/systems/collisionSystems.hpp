#pragma once
#include <include/raylib-cpp.hpp>

#include "../ecs/types.hpp"

class CollisionSystem: public SystemGroup {
public:
	ObjectID collisionCheck(ObjectID objectID, const Group &testObjects);
	void move(ObjectID objectID, raylib::Vector2 translation, const Group &collisionObjects);
};

struct CollisionObjects: public SystemGroup {};