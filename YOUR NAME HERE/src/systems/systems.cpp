#include "systems.hpp"
#include <cassert>

#include "../settings.hpp"
#include "../game.hpp"
#include "../ecs/ECSManager.hpp"

void systems::registerSystems() {

	globalManager.registerSystem<DrawTextured>({
		typeid(TextureComponent),
		typeid(PositionComponent),
		typeid(SizeComponent)
	});

	globalManager.registerSystem<DrawDebug>({
		typeid(PositionComponent),
		typeid(SizeComponent)
	});

	globalManager.registerSystem<AnimatedTextures>({
		typeid(AnimationInfo),
		typeid(TextureComponent)
	});

	globalManager.registerSystem<HealthSystem>({
		typeid(HealthComponent)
	});

	globalManager.registerSystem<PlayerInput>({});

	globalManager.registerSystem<MovementSystem>({
		typeid(PositionComponent),
		typeid(SizeComponent)
	});

	globalManager.registerSystem<CollisionSystem>({
		typeid(PositionComponent),
		typeid(SizeComponent)
	});

	globalManager.registerSystem<CollisionObjects>({
		typeid(PositionComponent),
		typeid(SizeComponent)
	});

	globalManager.registerSystem<DamageSystem>({
		typeid(DamageComponent)
	});

	globalManager.registerSystem<AIMovement>({
		typeid(Movement)
	});
}

void systems::updateSystems() {
	globalManager.updateSystem<PlayerInput>();
	globalManager.updateSystem<DamageSystem>();
	globalManager.updateSystem<HealthSystem>();
	globalManager.updateSystem<AnimatedTextures>();
	globalManager.updateSystem<AIMovement>();
}

void systems::drawSystems() {
	globalManager.updateSystem<DrawTextured>();
	globalManager.updateSystem<DrawDebug>();
}
