#include "objects.hpp"
#include "../game.hpp"

ObjectID createObject::TexturedRectangle(raylib::Vector2 position, raylib::Vector2 size, raylib::Texture *texture, raylib::Rectangle textureRect) { // Parameters for this kind of object
	uint16_t objectID = globalManager.createObject();	// Unique objectID used to identify the components as belonging to this object

	// Create components using this objectID and the parameters specified above
	globalManager.addComponent<PositionComponent>({objectID, position});
	globalManager.addComponent<SizeComponent>({objectID, size});
	globalManager.addComponent<TextureComponent>({objectID, texture, textureRect});

	// Add object to relevant systems
	systems::addToGroups(objectID, {&systems::moveableObjects});

	globalManager.addToSystem<DrawTextured>(objectID);

	return objectID;
}

ObjectID createObject::AnimatedTexture(raylib::Vector2 position, raylib::Vector2 size, raylib::Texture *texture, raylib::Rectangle textureRect, std::vector<uint8_t> frameSequence, float frameTime) {
	ObjectID objectID = createObject::TexturedRectangle(position, size, texture, textureRect);

	globalManager.addComponent<AnimationInfo>({objectID, textureRect.x, frameSequence, frameTime});

	globalManager.addToSystem<AnimatedTextures>(objectID);

	return objectID;
}

ObjectID createObject::Entity(raylib::Vector2 position, raylib::Vector2 size, raylib::Texture *texture, raylib::Rectangle textureRect, std::vector<uint8_t> frameSequence, float frameTime, float health) {
	ObjectID objectID = createObject::AnimatedTexture(position, size, texture, textureRect, frameSequence, frameTime);

	globalManager.addComponent<HealthComponent>({objectID, health});

	globalManager.addToSystem<HealthSystem>(objectID);

	return objectID;
}

ObjectID createObject::Damage(raylib::Vector2 position, raylib::Vector2 size, float damage, float cooldown, Group *targets) {
	uint16_t objectID = globalManager.createObject();	// Unique objectID used to identify the components as belonging to this object

	// Create components using this objectID and the parameters specified above
	globalManager.addComponent<PositionComponent>({objectID, position});
	globalManager.addComponent<SizeComponent>({objectID, size});
	globalManager.addComponent<DamageComponent>({objectID, damage, targets, cooldown});

	// Add object to relevant systems
	systems::addToGroups(objectID, {&systems::damageObjects});
	globalManager.addToSystem<DrawTextured>(objectID);

	return objectID;
}

ObjectID createObject::DamageAnimated(raylib::Vector2 position, raylib::Vector2 size, raylib::Texture *texture, raylib::Rectangle textureRect, std::vector<uint8_t> frameSequence, float frameTime, float damage, float cooldown, Group *targets) {
	ObjectID objectID = createObject::Damage(position, size, damage, cooldown, targets);

	globalManager.addToSystem<AnimatedTextures>(objectID);

	globalManager.addComponent<TextureComponent>({objectID, texture, textureRect});
	globalManager.addComponent<AnimationInfo>({objectID, textureRect.x, frameSequence, frameTime});

	return objectID;
}

ObjectID createObject::Enemy(raylib::Vector2 position, raylib::Vector2 size, raylib::Texture *texture, raylib::Rectangle textureRect, std::vector<uint8_t> frameSequence, float frameTime, float health, float damage, float cooldown) {
	ObjectID objectID = createObject::DamageAnimated(position, size, texture, textureRect, frameSequence, frameTime, damage, cooldown, globalManager.getSystemGroup<PlayerInput>());

	globalManager.addComponent<HealthComponent>({objectID, health});

	globalManager.addToSystem<HealthSystem>(objectID);

	return objectID;
}


ObjectID createObject::Player(raylib::Vector2 position, raylib::Texture *texture) {
	// Defaults for player
	raylib::Vector2 size{1, 1};
	raylib::Rectangle textureRect{128, 68, 16, 28};
	std::vector<uint8_t> frameSequence{0, 1, 2, 3};
	float frameTime = 0.2;
	float health = 100;

	ObjectID objectID = createObject::Entity(position, size, texture, textureRect, frameSequence, frameTime, health);

	assert(game::player == UINT16_MAX && "There is already a player created.");
	systems::addToGroups(objectID, {&systems::collisionObjects});

	globalManager.addToSystem<HealthSystem>(objectID);
	globalManager.addToSystem<PlayerInput>(objectID);

	return objectID;
}