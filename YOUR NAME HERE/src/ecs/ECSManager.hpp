#pragma once
#include "componentManager.hpp"
#include "signatureManager.hpp"
#include "systemsManager.hpp"

class ECSManager {
private:
	ComponentManager componentManager;
	SignatureManager signatureManager;
	
	ObjectID createdObjects = 0;

public:
	// Register new component
	template <typename Component>
	void newComponent() {
		componentManager.newComponentVector<Component>();
		signatureManager.newComponentSignature<Component>();
	}

	// Create object
	ObjectID createObject() {
		ObjectID objectID = createdObjects++;
		signatureManager.newObjectSignature(objectID);
		return objectID;
	}

	// Add component to an object
	template <typename Component>
	void addComponent(Component component) {
		componentManager.addComponent<Component>(component);
		signatureManager.addComponent<Component>(component.objectID);
	}

	// Remove a component from an object
	template <typename Component>
	void removeComponent(ObjectID objectID) {
		componentManager.removeComponent<Component>(objectID);
		signatureManager.removeComponent<Component>(objectID);
	}

	// Todo: Delete an object
	
	// Get a component belonging to an object
	template <typename Component>
	Component &getComponent(ObjectID objectID) {
		return componentManager.getComponent<Component>(objectID);
	}

	// Get an objects signature
	Signature getObjectSignature(ObjectID objectID) {
		return signatureManager.getObjectSignature(objectID);
	}
	
	// Get a components signature
	template <typename Component>
	Signature getObjectSignature() {
		return signatureManager.getComponentSignature<Component>();
	}
	
	// Get all components of a type
	template <typename Component>
	std::shared_ptr<ComponentVector<Component>> &getComponentVector(ObjectID objectID) {
		return componentManager.getComponentVector<Component>(objectID);
	}
};

inline ECSManager globalManager;