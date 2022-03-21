#include "AImovement.hpp"

#include "movementSystems.hpp"
#include "../ecs/ECSManager.hpp"
#include "../components/components.hpp"

void AIMovement::moveAI() {
	for (ObjectID objectID : group) {
		std::shared_ptr<MovementSystem> movementSystem = globalManager.getSystem<MovementSystem>();
		Movement movement = globalManager.getComponent<Movement>(objectID);

		movementSystem->move(objectID, movement.translation);
	}
}

void AIMovement::update() {
	moveAI();
}
