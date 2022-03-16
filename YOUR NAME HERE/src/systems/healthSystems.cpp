#include "healthSystems.hpp"

#include "../components/components.hpp"
#include "../ecs/ECSManager.hpp"
#include "../game.hpp"
#include "playerInput.hpp"

void HealthSystem::handleHealth() {
	for (ObjectID objectID : group) {
		HealthComponent health = globalManager.getComponent<HealthComponent>(objectID);
		if (health.health > 0) continue;

		globalManager.removeObject(objectID);
		Group *player = globalManager.getSystemGroup<PlayerInput>();
		if (objectID == *player->begin()) game::over = true;
	}
}
