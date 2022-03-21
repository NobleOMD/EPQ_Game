#include "ECSManager.hpp"

/// Create a signature from a list of component types
Signature ECSManager::createSignature(std::vector<std::type_index> components) {
	Signature signature;
	// Iterate over all the component types
	for (std::type_index component : components) {
		signature |= signatureManager.getComponentSignature(component); // Get the signauture and bitwise or it against the current signature
	}
	return signature; // Return finished signature
}

/// Create and return a new objectID according to the number of objects created so far

ObjectID ECSManager::createObject() {
	ObjectID objectID = createdObjects++;
	signatureManager.newObjectSignature(objectID);
	return objectID;
}

/// Add object to remove queue which is cleared before objects are drawn

void ECSManager::removeObject(ObjectID objectID) {
	// We have to have this queue because there are cases where removing an object during an iterative loop causes an error to be thrown. I
	// Instead we queue up all our objects to be removed all at once when they have been finished with.

	removeQueue.insert(objectID);
}

/// Remove all objects currently in the remove object queue

void ECSManager::removeObjects() {
	// Iterate over all the objects in the queue calling the remove object functions of all the managers.
	for (ObjectID objectID : removeQueue) {
		componentManager.removeObject(objectID);
		signatureManager.removeObject(objectID);
		systemManager.removeObject(objectID);
	}

	removeQueue.clear();	// Clear the queue so we don't try to remove all the objects again next frame.
}
