#include "systems.hpp"

#include "settings.hpp"
#include "game.hpp"
#include <cassert>

void systems::registerSystems() {
	globalManager.registerSystems({
		&drawTextured,
		&drawDebugging,
		&drawAnimated,
		&moveableObjects,
		&player,
		&enemies,
		&collisionObjects,
		&damageObjects
	});
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

// Drawing
//---------------------------------------------------------------------------------
void systems::drawTextures() {
	for (Group::iterator it = drawTextured.begin(); it != drawTextured.end(); it++) {
		ObjectID objectID = *it;

		TextureComponent textureComponent = globalManager.getComponent<TextureComponent>(objectID);
		PositionComponent position = globalManager.getComponent<PositionComponent>(objectID);
		SizeComponent size = globalManager.getComponent<SizeComponent>(objectID);

		// Janky texture offset that is used to align texture with collison box
		raylib::Vector2 textureOffset = (size.size * settings::tileSize) - (raylib::Vector2) textureComponent.rectangle.GetSize();

		textureComponent.texture->Draw(
			textureComponent.rectangle,
			(position.position * settings::tileSize) + raylib::Vector2(textureOffset.x / 2, textureOffset.y) // Move the texture inline with the collision box
		);
	}
}

void systems::drawDebug() {
	for (Group::iterator it = drawDebugging.begin(); it != drawDebugging.end(); it++) {
		ObjectID objectID = *it;

		PositionComponent position = globalManager.getComponent<PositionComponent>(objectID);
		SizeComponent size = globalManager.getComponent<SizeComponent>(objectID);

		raylib::Rectangle rectangle{position.position * settings::tileSize, size.size * settings::tileSize};
		rectangle.DrawLines(BLUE);
	}
}

void systems::tickAnimations() {
	for (Group::iterator it = drawAnimated.begin(); it != drawAnimated.end(); it++) {
		ObjectID objectID = *it;

		AnimationInfo &animationInfo = globalManager.getComponent<AnimationInfo>(objectID);
		FrameTimer &frameTimer = globalManager.getComponent<FrameTimer>(objectID);
		TextureComponent &textureComponent = globalManager.getComponent<TextureComponent>(objectID);

		// Update the timer
		frameTimer.timeRemaining -= GetFrameTime();
		if (frameTimer.timeRemaining >= 0) continue;
		else frameTimer.timeRemaining = frameTimer.timerLength;

		// If the timer completes a cycle tick through the animation
		animationInfo.frameIndex++;
		if (animationInfo.frameIndex >= animationInfo.frameSequence.size()) animationInfo.frameIndex = 0;

		// Update the texture rectangle according to the current frame
		float animationOffset = textureComponent.rectangle.width * animationInfo.frameSequence[animationInfo.frameIndex];
		textureComponent.rectangle.x = animationInfo.frameZero + animationOffset;
	}
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

// Input
//---------------------------------------------------------------------------------
void systems::handlePlayerInput() {
	if (player.size() == 0) return;
	ObjectID playerID = *player.begin();

	if (IsKeyPressed(KEY_W)) move(playerID, {0, -1}, collisionObjects);
	if (IsKeyPressed(KEY_A)) move(playerID, {-1, 0}, collisionObjects);
	if (IsKeyPressed(KEY_S)) move(playerID, {0, 1}, collisionObjects);
	if (IsKeyPressed(KEY_D)) move(playerID, {1, 0}, collisionObjects);

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
	damageObject.penetration--;
}

void systems::handleDamage() {
	for (Group::iterator it = damageObjects.begin(); it != damageObjects.end(); it++) {
		ObjectID objectID = *it;

		DamageComponent &damage = globalManager.getComponent<DamageComponent>(objectID);
		doDamage(damage, *damage.targets);
		if (damage.penetration <= 0) removeQueue.push_back(objectID);
	}
}
//---------------------------------------------------------------------------------