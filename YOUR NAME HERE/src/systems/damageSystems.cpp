#include "damageSystems.hpp"
#include "collisionSystems.hpp"
#include "../ecs/ECSManager.hpp"

void DamageSystem::handleDamage() {
	for (ObjectID objectID : group) {
		DamageComponent &damage = globalManager.getComponent<DamageComponent>(objectID);

		// Update the timer
		damage.timeRemaining -= GetFrameTime();
		if (damage.timeRemaining >= 0) continue;

		doDamage(damage, *damage.targets);
	}
}

void DamageSystem::doDamage(DamageComponent &damageObject, const Group &targetObjects) {
	std::shared_ptr<CollisionSystem> collisionSystem = globalManager.getSystem<CollisionSystem>();

	ObjectID collisionObject = collisionSystem->collisionCheck(damageObject.objectID, targetObjects);
	if (collisionObject == UINT16_MAX) return;

	HealthComponent &health = globalManager.getComponent<HealthComponent>(collisionObject);

	health.health -= damageObject.damage;
	damageObject.timeRemaining = damageObject.timerLength;
}

void DamageSystem::update() {
	handleDamage();
}