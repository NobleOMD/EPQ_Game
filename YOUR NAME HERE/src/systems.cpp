#include "systems.hpp"

void registerComponents() {
	componentManager.newComponent<PositionComponent>();
	componentManager.newComponent<SizeComponent>();
	componentManager.newComponent<TextureComponent>();
}

void draw() {
	for (Group::iterator it = drawnObjects.begin(); it != drawnObjects.end(); it++) {
		TextureComponent textureComponent = componentManager.getComponent<TextureComponent>(*it);
		PositionComponent position = componentManager.getComponent<PositionComponent>(*it);
		textureComponent.texture->Draw(textureComponent.rectangle, position.position);
	}
}
