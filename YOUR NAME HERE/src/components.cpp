#include "components.hpp"
#include "ecs/ECSManager.hpp"

void registerComponents() {
	globalManager.newComponent<PositionComponent>();
	globalManager.newComponent<SizeComponent>();
	globalManager.newComponent<TextureComponent>();
}