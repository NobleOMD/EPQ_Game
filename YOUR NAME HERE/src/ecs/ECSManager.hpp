#pragma once
#include "componentManager.hpp"
#include "signatureManager.hpp"
#include "systemsManager.hpp"

class ECSManager {
private:
	ObjectID createdObjects = 0;

	ComponentManager componentManager;
	SignatureManager signatureManager;
	SystemManager systemManager;

	std::vector<Group *> systemGroups;
	
	Group removeQueue;

public:
	// Components
	//----------------------------------------------------------------------------
	// Register new component
	template <typename Component>
	void registerComponent() {
		componentManager.newComponentVector<Component>();
		signatureManager.newComponentSignature<Component>();
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

	// Get a components signature
	template <typename Component>
	Signature getComponentSignature() {
		return signatureManager.getComponentSignature<Component>();
	}
	
	// Get a component belonging to an object
	template <typename Component>
	Component &getComponent(ObjectID objectID) {
		Signature objectSignature = signatureManager.getObjectSignature(objectID);
		Signature componentSignature = signatureManager.getComponentSignature<Component>();
		assert((objectSignature & componentSignature) == componentSignature && "Object does not have the requested component.");

		return componentManager.getComponent<Component>(objectID);
	}

	// Get all components of a type
	template <typename Component>
	std::shared_ptr<ComponentVector<Component>> &getComponentVector(ObjectID objectID) {
		return componentManager.getComponentVector<Component>(objectID);
	}

	Signature createSignature(std::vector<std::type_index> components) {
		Signature signature;
		for (std::type_index component : components) signature |= signatureManager.getComponentSignature(component);
		return signature;
	}
	//----------------------------------------------------------------------------

	// Objects
	//----------------------------------------------------------------------------
	// Create object
	ObjectID createObject() {
		ObjectID objectID = createdObjects++;
		signatureManager.newObjectSignature(objectID);
		return objectID;
	}

	void removeObject(ObjectID objectID) { removeQueue.insert(objectID); }

	void removeObjects() {
		for (ObjectID objectID : removeQueue) {
			for (Group *group : systemGroups) group->erase(objectID);
			componentManager.removeObject(objectID);
			signatureManager.removeObject(objectID);
			systemManager.removeObject(objectID);
		}
		removeQueue.clear();
	}

	// Get an objects signature
	Signature getObjectSignature(ObjectID objectID) {
		return signatureManager.getObjectSignature(objectID);
	}
	//----------------------------------------------------------------------------

	// Systems
	//----------------------------------------------------------------------------
	template <typename System>
	void registerSystem(Signature requiredComponents) {
		systemManager.newSystem<System>(requiredComponents);
	}

	template <typename System>
	void addToSystem(ObjectID objectID) { systemManager.addToSystem<System>(objectID); }

	template <typename System>
	void removeFromSystem(ObjectID objectID) { systemManager.removeFromSystem<System>(objectID); }

	template <typename System>
	void updateSystem() { systemManager.updateSystem<System>(); }
	//----------------------------------------------------------------------------
		
	// Old Systems
	//----------------------------------------------------------------------------
	void newSystem(Group *group) { systemGroups.push_back(group); }
	void registerSystems(std::vector<Group *> groups) {	for (Group *group : groups) newSystem(group); }
	//----------------------------------------------------------------------------
};

inline ECSManager globalManager;