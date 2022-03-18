#pragma once
#include "componentManager.hpp"
#include "signatureManager.hpp"
#include "systemsManager.hpp"

/// Main manager that covers the whole entity component system
class ECSManager {
private:
	ObjectID createdObjects = 0;

	ComponentManager componentManager;
	SignatureManager signatureManager;
	SystemManager systemManager;

	Group removeQueue;

public:
	// Components
	//----------------------------------------------------------------------------
	
	/// Register new component
	template <typename Component>
	void registerComponent() {
		componentManager.newComponentVector<Component>();
		signatureManager.newComponentSignature<Component>();
	}

	/// Add component to an object
	template <typename Component>
	void addComponent(Component component) {
		componentManager.addComponent<Component>(component);
		signatureManager.addComponent<Component>(component.objectID);
	}

	/// Remove a component from an object
	template <typename Component>
	void removeComponent(ObjectID objectID) {
		componentManager.removeComponent<Component>(objectID);
		signatureManager.removeComponent<Component>(objectID);
	}

	/// Get a components signature
	template <typename Component>
	Signature getComponentSignature() {
		return signatureManager.getComponentSignature<Component>();
	}

	/// Get a component belonging to an object
	template <typename Component>
	Component &getComponent(ObjectID objectID) {
		Signature objectSignature = signatureManager.getObjectSignature(objectID);
		Signature componentSignature = signatureManager.getComponentSignature<Component>();
		assert((objectSignature & componentSignature) == componentSignature && "Object does not have the requested component.");

		return componentManager.getComponent<Component>(objectID);
	}

	/// Get all components of a type
	template <typename Component>
	std::shared_ptr<ComponentVector<Component>> &getComponentVector(ObjectID objectID) {
		return componentManager.getComponentVector<Component>(objectID);
	}

	/// Create a signature from a list of component types
	Signature createSignature(std::vector<std::type_index> components) {
		Signature signature;
		// Iterate over all the component types
		for (std::type_index component : components) {
			signature |= signatureManager.getComponentSignature(component); // Get the signauture and bitwise or it against the current signature
		}
		return signature; // Return finished signature
	}
	//----------------------------------------------------------------------------

	// Objects
	//----------------------------------------------------------------------------
	
	/// Create and return a new objectID according to the number of objects created so far
	ObjectID createObject() {
		ObjectID objectID = createdObjects++;
		signatureManager.newObjectSignature(objectID);
		return objectID;
	}

	/// Add object to remove queue which is cleared before objects are drawn
	void removeObject(ObjectID objectID) {
		// We have to have this queue because there are cases where removing an object during an iterative loop causes an error to be thrown. I
		// Instead we queue up all our objects to be removed all at once when they have been finished with.

		removeQueue.insert(objectID);
	}

	/// Remove all objects currently in the remove object queue
	void removeObjects() {
		// Iterate over all the objects in the queue calling the remove object functions of all the managers.
		for (ObjectID objectID : removeQueue) {
			componentManager.removeObject(objectID);
			signatureManager.removeObject(objectID);
			systemManager.removeObject(objectID);
		}

		removeQueue.clear();	// Clear the queue so we don't try to remove all the objects again next frame.
	}
	//----------------------------------------------------------------------------

	// Systems
	//----------------------------------------------------------------------------
	
	/// Register a system with the system manager
	template <typename System>
	void registerSystem(std::vector<std::type_index> requiredComponents) {
		systemManager.registerSystem<System>(createSignature(requiredComponents));
	}

	/// Add an object to a system
	template <typename System>
	void addToSystem(ObjectID objectID) {
		Signature objectSignature = signatureManager.getObjectSignature(objectID);
		Signature systemSignature = systemManager.getSystemSignature<System>();
		assert((objectSignature & systemSignature) == systemSignature && "Object does not have components for system.");

		systemManager.addToSystem<System>(objectID);
	}

	/// Removing an object from a system
	template <typename System>
	void removeFromSystem(ObjectID objectID) { systemManager.removeFromSystem<System>(objectID); }

	/// Update specified system type
	template <typename System>
	void updateSystem() {
		systemManager.updateSystem<System>();
	}

	/// Get pointer to a system's group
	template <typename System>
	Group *getSystemGroup() {
		return systemManager.getGroup<System>();
	}

	/// Get the specified system
	template <typename System>
	std::shared_ptr<System> getSystem() {
		return systemManager.getSystem<System>();
	}
	//----------------------------------------------------------------------------
};

inline ECSManager globalManager;