#pragma once
#include <include/raylib-cpp.hpp>
#include <vector>

#include "ecs/ECSManager.hpp"
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
	
	inline Group collisionObjects;
	ObjectID collisionCheck(ObjectID objectID, const Group &createObject);
	void move(ObjectID objectID, raylib::Vector2 translation, const Group &collisionObjects);
}
