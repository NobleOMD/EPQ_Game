#include "types.hpp"

void BaseSystem::removeObject(ObjectID objectID) { 
	group.erase(objectID); 
}

void SystemGroup::update() {}
