#include "objects.hpp"

Actor::Actor(raylib::Vector2 position, raylib::Vector2 size, raylib::Texture *texture, raylib::Rectangle textureRect) { // Parameters for this kind of object
	uint16_t objectID = ecs::createdObjects++;	// Unique objectID used to identify the components as belonging to this object
	
	// Add object to relevant groups
	systems::entities.insert(objectID);
	systems::drawnObjects.insert(objectID);
	systems::moveableObjects.insert(objectID);

	// Create components using this objectID and the parameters specified above
	ecs::componentManager.addComponent<PositionComponent>({objectID, position});
	ecs::componentManager.addComponent<SizeComponent>({objectID, size});
	ecs::componentManager.addComponent<TextureComponent>({objectID, texture, textureRect});
};