#include "components.hpp"
#include "../ecs/ECSManager.hpp"

void components::registerComponents() {
	globalManager.registerComponent<PositionComponent>();
	globalManager.registerComponent<SizeComponent>();
	globalManager.registerComponent<TextureComponent>();
	globalManager.registerComponent<AnimationInfo>();
	globalManager.registerComponent<AnimationTimer>();
	globalManager.registerComponent<HealthComponent>();
	globalManager.registerComponent<DamageComponent>();
	globalManager.registerComponent<DamageTimer>();
	globalManager.registerComponent<Movement>();
}