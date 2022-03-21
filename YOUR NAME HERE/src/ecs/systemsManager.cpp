#include "systemsManager.hpp"

/// Remove an object from all systems
void SystemManager::removeObject(ObjectID objectID) {
	for (const std::shared_ptr<BaseSystem> &system : systems) {
		system->removeObject(objectID);
	}
}
