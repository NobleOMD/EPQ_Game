#include "componentManager.hpp"

/// Iterate over all the component vectors in the map and call their remove object function
void ComponentManager::removeObject(ObjectID objectID) {
	for (auto const &pair : componentVectors) {
		auto const &component = pair.second;
		component->removeObject(objectID);
	}
}
