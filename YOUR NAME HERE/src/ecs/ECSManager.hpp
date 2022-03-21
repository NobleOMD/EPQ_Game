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
	Signature createSignature(std::vector<std::type_index> components);
	//----------------------------------------------------------------------------

	// Objects
	//----------------------------------------------------------------------------
	
	/// Create and return a new objectID according to the number of objects created so far
	ObjectID createObject();

	/// Add object to remove queue which is cleared before objects are drawn
	void removeObject(ObjectID objectID);

	/// Remove all objects currently in the remove object queue
	void removeObjects();
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