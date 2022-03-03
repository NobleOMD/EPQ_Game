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

		raylib::Rectangle rectangle{position.position, size.size};
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

	if (IsKeyPressed(KEY_W)) move(playerID, {0, -1});
	if (IsKeyPressed(KEY_A)) move(playerID, {-1, 0});
	if (IsKeyPressed(KEY_S)) move(playerID, {0, 1});
	if (IsKeyPressed(KEY_D)) move(playerID, {1, 0});
}

void systems::handleCollisions() {
	for (Group::iterator it = collidableObjects.begin(); it != collidableObjects.end(); it++) {
		ObjectID objectID = *it;
		PositionComponent &position = ecs::componentManager.getComponent<PositionComponent>(objectID);
		SizeComponent &size = ecs::componentManager.getComponent<SizeComponent>(objectID);

		for (float i = 0; i < size.size.x; i++) {
			for (float j = 0; i < size.size.y; i++) {
			}
		}
	}
}
