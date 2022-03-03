#pragma once
#include <include/raylib-cpp.hpp>
#include "ecs/entityComponentSystem.hpp"
#include "systems.hpp"
#include "components.hpp"

struct Actor {
	Actor(raylib::Vector2 position, raylib::Vector2 size, raylib::Texture *texture, raylib::Rectangle textureRect) { // Parameters for this kind of object
		uint16_t objectID = createdObjects++;	// Unique objectID used to identify the components as belonging to this object
		entities.insert(objectID);
		drawnObjects.insert(objectID);

		// Create components using this objectID and the parameters specified above
		componentManager.addComponent<PositionComponent>({objectID, position});
		componentManager.addComponent<SizeComponent>({objectID, size});
		componentManager.addComponent<TextureComponent>({objectID, texture, textureRect});
	};
};