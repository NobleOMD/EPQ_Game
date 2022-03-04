#include "systems.hpp"

#include "settings.hpp"
#include "game.hpp"
#include <cassert>

void systems::addToGroups(ObjectID objectID, std::vector<Group *> groups) {
	entities.insert(objectID);
	for (Group *group : groups) group->insert(objectID);
}

void systems::drawTextured() {
	for (Group::iterator it = drawnObjects.begin(); it != drawnObjects.end(); it++) {
		TextureComponent textureComponent = ecs::componentManager.getComponent<TextureComponent>(*it);
		PositionComponent position = ecs::componentManager.getComponent<PositionComponent>(*it);
		SizeComponent size = ecs::componentManager.getComponent<SizeComponent>(*it);

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
		PositionComponent position = ecs::componentManager.getComponent<PositionComponent>(*it);
		SizeComponent size = ecs::componentManager.getComponent<SizeComponent>(*it);

		raylib::Rectangle rectangle{position.position * settings::tileSize, size.size * settings::tileSize};
		rectangle.DrawLines(BLUE);
	}
}

void systems::move(ObjectID objectID, raylib::Vector2 translation) {
	assert(moveableObjects.find(objectID) != moveableObjects.end() && "This object is not a moveable object.");

	PositionComponent &position = ecs::componentManager.getComponent<PositionComponent>(objectID);
	SizeComponent &size = ecs::componentManager.getComponent<SizeComponent>(objectID);

	position.position += translation;
	game::clampWithin(settings::gridSize, position.position, size.size); // Clamp within the overall grid
}

void systems::handlePlayerInput() {
	if (playerInput.size() == 0) return;
	ObjectID playerID = *playerInput.begin();

	if (IsKeyPressed(KEY_W)) move(playerID, {0, -1}, collisionObjects);
	if (IsKeyPressed(KEY_A)) move(playerID, {-1, 0}, collisionObjects);
	if (IsKeyPressed(KEY_S)) move(playerID, {0, 1}, collisionObjects);
	if (IsKeyPressed(KEY_D)) move(playerID, {1, 0}, collisionObjects);

	
}

ObjectID systems::collisionCheck(ObjectID objectID, const Group &objects) {
	raylib::Rectangle targetRectangle{
		ecs::componentManager.getComponent<PositionComponent>(objectID).position,
		ecs::componentManager.getComponent<SizeComponent>(objectID).size
	};

	// Check for collision within a list of objects with collison
	for (ObjectID testObject : objects) {
		if (objectID == testObject) continue; // If the targetRectangle is ourself continue.

		raylib::Rectangle testRectangle{
			ecs::componentManager.getComponent<PositionComponent>(testObject).position,
			ecs::componentManager.getComponent<SizeComponent>(testObject).size
		};

		// If this objects hit box is colliding, handle by returning the objectID
		if (CheckCollisionRecs(targetRectangle, testRectangle)) return testObject;
	}

	return -1; // If no collision is found return -1
}

void systems::move(ObjectID objectID, raylib::Vector2 translation, const Group &collisionObjects) {
	move(objectID, translation);
	if (collisionCheck(objectID, collisionObjects) != UINT16_MAX) move(objectID, -translation);
}