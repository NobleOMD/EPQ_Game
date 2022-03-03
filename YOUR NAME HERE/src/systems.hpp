#pragma once
#include <include/raylib-cpp.hpp>

#include "ecs/entityComponentSystem.hpp"
#include "components.hpp"

namespace systems
{
	inline Group entities;				// All objectID's

	inline Group drawnObjects;			// Requires Texture, Position components
	void drawTextured();				// Draws all objects within above group

	inline Group moveableObjects;
	void move(ObjectID objectID, raylib::Vector2 translation);

	inline Group playerInput;
	void handlePlayerInput();
}
