#include "entityComponentSystem.hpp"

void registerComponents() {
	componentManager.newComponent<PositionComponent>();
	componentManager.newComponent<SizeComponent>();
	componentManager.newComponent<TextureComponent>();
}