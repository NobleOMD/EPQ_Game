#include "movementSystems.hpp"
#include <cassert>

#include "../components/components.hpp"
#include "../settings.hpp"
#include "../ecs/ECSManager.hpp"
#include "miscFunctions.hpp"

void MovementSystem::move(ObjectID objectID, raylib::Vector2 translation) {
	assert(group.find(objectID) != group.end() && "Object is not moveable.");

	PositionComponent &position = globalManager.getComponent<PositionComponent>(objectID);
	SizeComponent &size = globalManager.getComponent<SizeComponent>(objectID);

	position.position += translation;
	functions::clampWithin(settings::gridSize, position.position, size.size); // Clamp within the overall grid
}
