#include "objects.hpp"

ObjectID createObject::Actor(raylib::Vector2 position, raylib::Vector2 size, raylib::Texture *texture, raylib::Rectangle textureRect) { // Parameters for this kind of object
	uint16_t objectID = globalManager.createObject();	// Unique objectID used to identify the components as belonging to this object

	// Add object to relevant systems
	systems::addToGroups(objectID, {&systems::drawTextured, &systems::moveableObjects, &systems::collisionObjects});

	// Create components using this objectID and the parameters specified above
	globalManager.addComponent<PositionComponent>({objectID, position});
	globalManager.addComponent<SizeComponent>({objectID, size});
	globalManager.addComponent<TextureComponent>({objectID, texture, textureRect});

	return objectID;
}

ObjectID createObject::AnimatedActor(raylib::Vector2 position, raylib::Vector2 size, raylib::Texture *texture, raylib::Rectangle textureRect, std::vector<uint8_t> frameOrder, float frameTime) {
	ObjectID objectID = createObject::Actor(position, size, texture, textureRect);

	systems::addToGroups(objectID, {&systems::drawAnimated});

	globalManager.addComponent<AnimationInfo>({objectID, textureRect.x, frameOrder});
	globalManager.addComponent<FrameTimer>({objectID, frameTime});

	return objectID;
}


ObjectID createObject::Player(raylib::Vector2 position, raylib::Vector2 size, raylib::Texture *texture, raylib::Rectangle textureRect, std::vector<uint8_t> frameOrder, float frameTime) {
	ObjectID objectID = createObject::AnimatedActor(position, size, texture, textureRect, frameOrder, frameTime);
	assert(systems::playerInput.size() == 0 && "There is already a player created.");
	systems::playerInput.insert(objectID);

	return objectID;
}
