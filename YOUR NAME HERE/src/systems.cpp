#include "systems.hpp"
#include "settings.hpp"
#include "game.hpp"
#include <cassert>

void drawTextured() {
	for (Group::iterator it = drawnObjects.begin(); it != drawnObjects.end(); it++) {
		TextureComponent textureComponent = componentManager.getComponent<TextureComponent>(*it);
		PositionComponent position = componentManager.getComponent<PositionComponent>(*it);
		textureComponent.texture->Draw(textureComponent.rectangle, position.position);
	}
}

void move(ObjectID objectID, raylib::Vector2 translation) {
	assert(moveableObjects.find(objectID) != moveableObjects.end() && "This object is not a moveable object.");

	PositionComponent &position = componentManager.getComponent<PositionComponent>(objectID);
	SizeComponent &size = componentManager.getComponent<SizeComponent>(objectID);

	position.position += translation;
	game::clampWithin(settings::screenSize, position.position, size.size); // Clamp within the overall grid
}

void handlePlayerInput() {
	if (playerInput.size() == 0) return;
	ObjectID playerID = *playerInput.begin();

	if (IsKeyPressed(KEY_W)) move(playerID, {0, -settings::tileSize});
	if (IsKeyPressed(KEY_A)) move(playerID, {-settings::tileSize, 0});
	if (IsKeyPressed(KEY_S)) move(playerID, {0, settings::tileSize});
	if (IsKeyPressed(KEY_D)) move(playerID, {settings::tileSize, 0});
}
