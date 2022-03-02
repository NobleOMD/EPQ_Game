#pragma once
#include <include/raylib-cpp.hpp>
#include "ecs/entityComponentSystem.hpp"
#include "systems.hpp"
#include "components.hpp"

struct Actor {
	Actor(raylib::Vector2 position, raylib::Vector2 size, raylib::Texture *texture, raylib::Rectangle textureRect) {
		uint16_t objectID = createdObjects++;
		entities.insert(objectID);
		drawnObjects.insert(objectID);
		componentManager.addComponent<PositionComponent>({objectID, position});
		componentManager.addComponent<SizeComponent>({objectID, size});
		componentManager.addComponent<TextureComponent>({objectID, texture, textureRect});
	};
};