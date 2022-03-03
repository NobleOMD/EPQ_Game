#pragma once
#include <include/raylib-cpp.hpp>
#include <vector>

#include "ecs/entityComponentSystem.hpp"
#include "components.hpp"

namespace systems
{
	void addToGroups(ObjectID objectID, std::vector<Group *> groups);

	inline Group entities;				// All objectID's

	inline Group drawnObjects;			// Requires Texture, Size, and Position components
	void drawTextured();				// Draws all objects within above group

	inline Group drawDebugging;
	void drawDebug();

	inline Group moveableObjects;
	void move(ObjectID objectID, raylib::Vector2 translation);

	inline Group playerInput;
	void handlePlayerInput();

	inline Group collidableObjects;		// Must have collision rectangle component
	inline std::set<int> occupied;
	void handleCollisions();
}
