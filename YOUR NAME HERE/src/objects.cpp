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

ObjectID createObject::AnimatedActor(raylib::Vector2 position, raylib::Vector2 size, raylib::Texture *texture, raylib::Rectangle textureRect, std::vector<uint8_t> frameSequence, float frameTime) {
	ObjectID objectID = createObject::Actor(position, size, texture, textureRect);

	systems::addToGroups(objectID, {&systems::drawAnimated});

	globalManager.addComponent<AnimationInfo>({objectID, textureRect.x, frameSequence});
	globalManager.addComponent<FrameTimer>({objectID, frameTime});

	return objectID;
}

ObjectID createObject::Entity(raylib::Vector2 position, raylib::Vector2 size, raylib::Texture *texture, raylib::Rectangle textureRect, std::vector<uint8_t> frameSequence, float frameTime, float health) {
	ObjectID objectID = createObject::AnimatedActor(position, size, texture, textureRect, frameSequence, frameTime);

	globalManager.addComponent<HealthComponent>({objectID, health});
	
	return objectID;
}

ObjectID createObject::Enemy(raylib::Vector2 position, raylib::Vector2 size, raylib::Texture *texture, raylib::Rectangle textureRect, std::vector<uint8_t> frameSequence, float frameTime, float health) {
	ObjectID objectID = createObject::Entity(position, size, texture, textureRect, frameSequence, frameTime, health);

	systems::addToGroups(objectID, {&systems::enemies});

	return objectID;
}


ObjectID createObject::Player(raylib::Vector2 position, raylib::Vector2 size, raylib::Texture *texture, raylib::Rectangle textureRect, std::vector<uint8_t> frameSequence, float frameTime, float health) {
	ObjectID objectID = createObject::Entity(position, size, texture, textureRect, frameSequence, frameTime, health);
	
	assert(systems::player.size() == 0 && "There is already a player created.");
	systems::addToGroups(objectID, {&systems::player});

	return objectID;
}

ObjectID createObject::DamagePlayer(raylib::Vector2 position, raylib::Vector2 size, raylib::Texture *texture, raylib::Rectangle textureRect, float damage, uint8_t penetration) {
	uint16_t objectID = globalManager.createObject();	// Unique objectID used to identify the components as belonging to this object

	// Add object to relevant systems
	systems::addToGroups(objectID, {&systems::drawTextured, &systems::damageObjects});

	// Create components using this objectID and the parameters specified above
	globalManager.addComponent<PositionComponent>({objectID, position});
	globalManager.addComponent<SizeComponent>({objectID, size});
	globalManager.addComponent<TextureComponent>({objectID, texture, textureRect});
	globalManager.addComponent<DamageComponent>({objectID, damage, penetration, &systems::player});

	return objectID;
}
