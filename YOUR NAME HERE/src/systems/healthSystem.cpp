#include "healthSystem.hpp"
#include "../components/components.hpp"
#include "../ecs/ECSManager.hpp"
#include "../game.hpp"

void HealthSystem::handleHealth() {
	for (ObjectID objectID : group) {
		HealthComponent health = globalManager.getComponent<HealthComponent>(objectID);
		if (health.health > 0) continue;

		globalManager.removeObject(objectID);
		if (objectID == game::player) game::over = true;
	}
}
