#include "systems.hpp"
#include <cassert>

#include "../settings.hpp"
#include "../game.hpp"

void systems::registerSystems() {
	globalManager.registerSystems({
		&moveableObjects,
		&collisionObjects,
		&damageObjects
	});

	globalManager.registerSystem<DrawTextured>({
		typeid(TextureComponent),
		typeid(PositionComponent),
		typeid(SizeComponent)
	});

	globalManager.registerSystem<DrawDebug>({
		typeid(PositionComponent),
		typeid(SizeComponent)
	});

	globalManager.registerSystem<AnimatedTextures>({
		typeid(AnimationInfo),
		typeid(TextureComponent)
	});

	globalManager.registerSystem<HealthSystem>({
		typeid(HealthComponent)
	});

	globalManager.registerSystem<PlayerInput>({});
}

// Basic system functions
//---------------------------------------------------------------------------------
void systems::addToGroups(ObjectID objectID, std::vector<Group *> groups) {
	for (Group *group : groups) group->insert(objectID);
}

bool systems::hasComponents(ObjectID objectID, Signature requiredComponents) {
	return (globalManager.getObjectSignature(objectID) & requiredComponents) == requiredComponents;
}
//---------------------------------------------------------------------------------

// Movement
//---------------------------------------------------------------------------------
void systems::move(ObjectID objectID, raylib::Vector2 translation) {
	assert(moveableObjects.find(objectID) != moveableObjects.end() && "This object is not a moveable object.");

	PositionComponent &position = globalManager.getComponent<PositionComponent>(objectID);
	SizeComponent &size = globalManager.getComponent<SizeComponent>(objectID);

	position.position += translation;
	game::clampWithin(settings::gridSize, position.position, size.size); // Clamp within the overall grid
}
//---------------------------------------------------------------------------------

// Collision
//---------------------------------------------------------------------------------
ObjectID systems::collisionCheck(ObjectID objectID, const Group &testObjects) {

	raylib::Rectangle targetRectangle{
		globalManager.getComponent<PositionComponent>(objectID).position,
		globalManager.getComponent<SizeComponent>(objectID).size
	};

	// Check for collision within a list of objects with collison
	for (ObjectID testObject : testObjects) {
		if (objectID == testObject) continue; // If the targetRectangle is ourself continue.

		raylib::Rectangle testRectangle{
			globalManager.getComponent<PositionComponent>(testObject).position,
			globalManager.getComponent<SizeComponent>(testObject).size
		};

		// If this objects hit box is colliding, handle by returning the objectID
		if (CheckCollisionRecs(targetRectangle, testRectangle)) return testObject;
	}

	return UINT16_MAX; // If no collision is found return max value for objectID
}

void systems::move(ObjectID objectID, raylib::Vector2 translation, const Group &collisionObjects) {
	move(objectID, translation);
	if (collisionCheck(objectID, collisionObjects) != UINT16_MAX) move(objectID, -translation);
}

void systems::doDamage(DamageComponent &damageObject, const Group &collisionObjects) {
	ObjectID collisionObject = collisionCheck(damageObject.objectID, collisionObjects);
	if (collisionObject == UINT16_MAX) return;

	HealthComponent &health = globalManager.getComponent<HealthComponent>(collisionObject);

	health.health -= damageObject.damage;
	damageObject.timeRemaining = damageObject.timerLength;
}

void systems::handleDamage() {
	for (ObjectID objectID : damageObjects) {
		DamageComponent &damage = globalManager.getComponent<DamageComponent>(objectID);

		// Update the timer
		damage.timeRemaining -= GetFrameTime();
		if (damage.timeRemaining >= 0) continue;

		doDamage(damage, *damage.targets);
	}
}
//---------------------------------------------------------------------------------