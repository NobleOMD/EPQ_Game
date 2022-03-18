#pragma once
#include <unordered_map>
#include <typeindex>

#include "types.hpp"

class SignatureManager {
private:
	std::unordered_map<ObjectID, Signature> objectID_signature;
	std::unordered_map<std::type_index, Signature> componentSignatures;

public:
	/// Add component signature to dataset
	template <typename Component>
	void newComponentSignature() {
		std::type_index typeName = typeid(Component);
		Signature signature;
		componentSignatures[typeName] = signature.set(componentSignatures.size());
	};

	/// Add objectID to | ObjectID : Signature | map
	void newObjectSignature(ObjectID objectID) {
		Signature newSignature = 0b0000;
		objectID_signature[objectID] = newSignature;
	};

	/// Add component to object
	template <typename Component>
	void addComponent(ObjectID objectID) {
		Signature componentSignature = getComponentSignature<Component>();
		objectID_signature[objectID] |= componentSignature;		// Bitwise OR the component signature with the current signature
	};

	/// Remove component from object
	template <typename Component>
	void removeComponent(ObjectID objectID) {
		Signature componentSignature = getComponentSignature<Component>();
		objectID_signature[objectID] ^= componentSignature;		// Bitwise XOR the component signature with the current signature
	};

	/// Remove objectID from | ObjectID : Signature | map
	void removeObject(ObjectID objectID) {
		objectID_signature.erase(objectID);
	};

	/// Get signature by component
	template <typename Component>
	Signature getComponentSignature() {
		std::type_index typeName = typeid(Component);
		return componentSignatures[typeName];
	};

	/// Get the signature of component by type
	Signature getComponentSignature(std::type_index typeName) {
		return componentSignatures[typeName];
	};

	/// Get signature by objectID
	Signature getObjectSignature(ObjectID objectID) {
		return objectID_signature[objectID];
	};
};