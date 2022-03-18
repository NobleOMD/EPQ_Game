#include "objects.hpp"
#include "../game.hpp"

ObjectID createObject::TexturedRectangle(raylib::Vector2 position, raylib::Vector2 size, raylib::Texture *texture, raylib::Rectangle textureRect) { // Parameters for this kind of object
	uint16_t objectID = globalManager.createObject();	// Unique objectID used to identify the components as belonging to this object

	// Create components using this objectID and the parameters specified above
	globalManager.addComponent<PositionComponent>({objectID, position});
	globalManager.addComponent<SizeComponent>({objectID, size});
	globalManager.addComponent<TextureComponent>({objectID, texture, textureRect});

	globalManager.addToSystem<DrawTextured>(objectID);

	return objectID;
}

ObjectID createObject::AnimatedTexture(raylib::Vector2 position, raylib::Vector2 size, raylib::Texture *texture, raylib::Rectangle textureRect, std::vector<uint8_t> frameSequence, float frameTime) {
	ObjectID objectID = createObject::TexturedRectangle(position, size, texture, textureRect);

	globalManager.addComponent<AnimationInfo>({objectID, textureRect.x, frameSequence});
	globalManager.addComponent<AnimationTimer>({objectID, frameTime, frameTime});

	globalManager.addToSystem<AnimatedTextures>(objectID);

	return objectID;
}

ObjectID createObject::Entity(raylib::Vector2 position, raylib::Vector2 size, raylib::Texture *texture, raylib::Rectangle textureRect, std::vector<uint8_t> frameSequence, float frameTime, float health) {
	ObjectID objectID = createObject::AnimatedTexture(position, size, texture, textureRect, frameSequence, frameTime);

	globalManager.addComponent<HealthComponent>({objectID, health});

	globalManager.addToSystem<MovementSystem>(objectID);
	globalManager.addToSystem<HealthSystem>(objectID);

	return objectID;
}

ObjectID createObject::Damage(raylib::Vector2 position, raylib::Vector2 size, float damage, float cooldown, Group *targets) {
	uint16_t objectID = globalManager.createObject();	// Unique objectID used to identify the components as belonging to this object

	// Create components using this objectID and the parameters specified above
	globalManager.addComponent<PositionComponent>({objectID, position});
	globalManager.addComponent<SizeComponent>({objectID, size});
	globalManager.addComponent<DamageComponent>({objectID, damage, targets, cooldown});

	globalManager.addToSystem<DamageSystem>(objectID);

	return objectID;
}

ObjectID createObject::DamageAnimated(raylib::Vector2 position, raylib::Vector2 size, raylib::Texture *texture, raylib::Rectangle textureRect, std::vector<uint8_t> frameSequence, float frameTime, float damage, float cooldown, Group *targets) {
	ObjectID objectID = createObject::Damage(position, size, damage, cooldown, targets);

	globalManager.addComponent<TextureComponent>({objectID, texture, textureRect});
	globalManager.addComponent<AnimationInfo>({objectID, textureRect.x, frameSequence});
	globalManager.addComponent<AnimationTimer>({objectID, frameTime, 0});

	globalManager.addToSystem<DrawTextured>(objectID);
	globalManager.addToSystem<AnimatedTextures>(objectID);

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

	assert(globalManager.getSystemGroup<PlayerInput>()->size() == 0 && "There is already a player created.");

	globalManager.addToSystem<CollisionObjects>(objectID);
	globalManager.addToSystem<HealthSystem>(objectID);
	globalManager.addToSystem<PlayerInput>(objectID);

	return objectID;
}

ObjectID createObject::Wall(raylib::Vector2 position, raylib::Vector2 size) {
	ObjectID objectID = globalManager.createObject();

	globalManager.addComponent<PositionComponent>({objectID, position});
	globalManager.addComponent<SizeComponent>({objectID, size});

	globalManager.addToSystem<CollisionObjects>(objectID);

	return objectID;
}

ObjectID createObject::Spikes(raylib::Vector2 position, raylib::Texture *texture, Group *targets) {
	raylib::Vector2 size{1, 1};							// Size
	raylib::Rectangle textureRect{16, 176, 16, 16};		// Texture sub-rectangle
	std::vector<uint8_t> frameSequence{0, 1, 2, 3};		// Animation frame sequence
	float frameTime = 0.075;							// Animation frame duration
	float damage = 100;									// Damage
	float damageCooldown = 0.2;							// Cooldown

	ObjectID objectID = DamageAnimated(position, size, texture, textureRect, frameSequence, frameTime, damage, damageCooldown, targets);

	return objectID;
}

ObjectID createObject::BigDemon(raylib::Vector2 position, raylib::Texture *texture) {
	raylib::Vector2 size{1, 2};
	raylib::Rectangle textureRect{16, 364, 32, 36};
	std::vector<uint8_t> frameSequence{0, 1, 2, 3};
	float frameTime = 0.3;
	float health = 100;
	float damage = 100;
	float damageCooldown = 1.2;

	ObjectID objectID = Enemy(position, size, texture, textureRect, frameSequence, frameTime, health, damage, damageCooldown);

	return objectID;
}