#pragma once
#include <unordered_map>
#include <typeindex>

#include "types.hpp"

class SignatureManager {
private:
	std::unordered_map<ObjectID, Signature> objectID_signature;
	std::unordered_map<std::type_index, Signature> componentSignatures;

public:
	// Add component signature
	template <typename Component>
	void newComponentSignature() {
		std::type_index typeName = typeid(Component);
		componentSignatures[typeName] = 0b0001 << componentSignatures.size();
	};

	// Add objectID
	void newObjectSignature(ObjectID objectID) {
		Signature newSignature = 0b0000;
		objectID_signature[objectID] = newSignature;
	};

	// Add component to objectID
	template <typename Component>
	void addComponent(ObjectID objectID) {
		Signature componentSignature = getComponentSignature<Component>();
		objectID_signature[objectID] |= componentSignature;		// Bitwise OR the component signature with the current signature
	};

	// Remove component from objectID
	template <typename Component>
	void removeComponent(ObjectID objectID) {
		Signature componentSignature = getComponentSignature<Component>();
		objectID_signature[objectID] ^= componentSignature;		// Bitwise XOR the component signature with the current signature
	};

	// Remove objectID
	void removeObject(ObjectID objectID) {
		objectID_signature.erase(objectID);
	};

	// Get signature by component
	template <typename Component>
	Signature getComponentSignature() {
		std::type_index typeName = typeid(Component);
		return componentSignatures[typeName];
	};

	// Get signature by objectID
	Signature getObjectSignature(ObjectID objectID) {
		return objectID_signature[objectID];
	};
};