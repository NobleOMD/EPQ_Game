#include "collisionSystems.hpp"

#include "../ecs/ECSManager.hpp"
#include "../components/components.hpp"
#include "movementSystems.hpp"

ObjectID CollisionSystem::collisionCheck(ObjectID objectID, const Group &testObjects) {

	raylib::Rectangle targetRectangle{
		globalManager.getComponent<PositionComponent>(objectID).position,
		globalManager.getComponent<SizeComponent>(objectID).size
	};

	// Check for collision within a list of objects with collison
	for (ObjectID testObject : testObjects) {
		if (objectID == testObject) continue; // If the targetRectangle is ourself continue.

		raylib::Rectangle testRectangle{
			globalManager.getComponent<PositionComponent>(testObject).position,
			globalManager.getComponent<SizeComponent>(testObject).size
		};

		// If this objects hit box is colliding, handle by returning the objectID
		if (CheckCollisionRecs(targetRectangle, testRectangle)) return testObject;
	}

	return UINT16_MAX; // If no collision is found return max value for objectID
}

void CollisionSystem::move(ObjectID objectID, raylib::Vector2 translation, const Group &collisionObjects) {
	std::shared_ptr<MovementSystem> movementSystem = globalManager.getSystem<MovementSystem>();

	movementSystem->move(objectID, translation);
	if (collisionCheck(objectID, collisionObjects) != UINT16_MAX) movementSystem->move(objectID, -translation);
}
