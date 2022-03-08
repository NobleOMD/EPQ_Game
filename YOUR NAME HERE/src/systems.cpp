#include "systems.hpp"

#include "settings.hpp"
#include "game.hpp"
#include <cassert>

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
void systems::drawTextured() {
	Signature drawSignature = globalManager.createSignature({typeid(PositionComponent), typeid(SizeComponent), typeid(TextureComponent)});
	for (Group::iterator it = drawnObjects.begin(); it != drawnObjects.end(); it++) {
		ObjectID objectID = *it;
		assert(hasComponents(objectID, drawSignature) && "This object does not have the correct compontents to draw.");
		
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
		PositionComponent position = globalManager.getComponent<PositionComponent>(*it);
		SizeComponent size = globalManager.getComponent<SizeComponent>(*it);

		raylib::Rectangle rectangle{position.position * settings::tileSize, size.size * settings::tileSize};
		rectangle.DrawLines(BLUE);
	}
}

//---------------------------------------------------------------------------------

// Movement
//---------------------------------------------------------------------------------
void systems::move(ObjectID objectID, raylib::Vector2 translation) {
	Signature moveSignature = globalManager.createSignature( {typeid(PositionComponent), typeid(SizeComponent)} );
	assert(moveableObjects.find(objectID) != moveableObjects.end() && "This object is not a moveable object.");
	assert(hasComponents(objectID, moveSignature) && "Object does not have the correct components for movement.");

	PositionComponent &position = globalManager.getComponent<PositionComponent>(objectID);
	SizeComponent &size = globalManager.getComponent<SizeComponent>(objectID);

	position.position += translation;
	game::clampWithin(settings::gridSize, position.position, size.size); // Clamp within the overall grid
}
//---------------------------------------------------------------------------------

// Input
//---------------------------------------------------------------------------------
void systems::handlePlayerInput() {
	if (playerInput.size() == 0) return;
	ObjectID playerID = *playerInput.begin();

	if (IsKeyPressed(KEY_W)) move(playerID, {0, -1}, collisionObjects);
	if (IsKeyPressed(KEY_A)) move(playerID, {-1, 0}, collisionObjects);
	if (IsKeyPressed(KEY_S)) move(playerID, {0, 1}, collisionObjects);
	if (IsKeyPressed(KEY_D)) move(playerID, {1, 0}, collisionObjects);


}
//---------------------------------------------------------------------------------

// Collision
//---------------------------------------------------------------------------------
ObjectID systems::collisionCheck(ObjectID objectID, const Group &createObject) {
	raylib::Rectangle targetRectangle{
		globalManager.getComponent<PositionComponent>(objectID).position,
		globalManager.getComponent<SizeComponent>(objectID).size
	};

	// Check for collision within a list of objects with collison
	for (ObjectID testObject : createObject) {
		if (objectID == testObject) continue; // If the targetRectangle is ourself continue.

		raylib::Rectangle testRectangle{
			globalManager.getComponent<PositionComponent>(testObject).position,
			globalManager.getComponent<SizeComponent>(testObject).size
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
//---------------------------------------------------------------------------------