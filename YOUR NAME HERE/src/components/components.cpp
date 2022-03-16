#include "components.hpp"
#include "../ecs/ECSManager.hpp"

void registerComponents() {
	globalManager.registerComponent<PositionComponent>();
	globalManager.registerComponent<SizeComponent>();
	globalManager.registerComponent<TextureComponent>();
	globalManager.registerComponent<AnimationInfo>();
	globalManager.registerComponent<HealthComponent>();
	globalManager.registerComponent<DamageComponent>();
}