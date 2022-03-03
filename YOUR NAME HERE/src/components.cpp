#include "components.hpp"
#include "ecs/entityComponentSystem.hpp"

void ecs::registerComponents() {
	componentManager.newComponent<PositionComponent>();
	componentManager.newComponent<SizeComponent>();
	componentManager.newComponent<TextureComponent>();
}