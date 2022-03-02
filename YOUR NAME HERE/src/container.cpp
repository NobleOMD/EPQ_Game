#include "container.hpp"

Actor::Actor(raylib::Vector2 position, raylib::Vector2 size, raylib::Texture *texture, raylib::Rectangle textureRect) {
	uint16_t objectID = createdObjects++;
	entities.insert(objectID);
	drawnObjects.insert(objectID);
	componentManager.addComponent<PositionComponent>({objectID, position});
	componentManager.addComponent<SizeComponent>({objectID, size});
	componentManager.addComponent<TextureComponent>({objectID, texture, textureRect});
}

void registerComponents() {
	componentManager.newComponent<PositionComponent>();
	componentManager.newComponent<SizeComponent>();
	componentManager.newComponent<TextureComponent>();
}

void drawECS() {
	for (Group::iterator it = drawnObjects.begin(); it != drawnObjects.end(); it++) {
		TextureComponent textureComponent = componentManager.getComponent<TextureComponent>(*it);
		PositionComponent position = componentManager.getComponent<PositionComponent>(*it);
		textureComponent.texture->Draw(textureComponent.rectangle, position.position);
	}
}
