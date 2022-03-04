#pragma once
#include "types.hpp"
#include "entityComponentSystem.hpp"

class SignatureManager {
private:
	std::unordered_map<ObjectID, Signature> objectID_signature;
	std::unordered_map<std::type_index, Signature> componentSignatures;

public:
	// Add objectID
	// Add component signature
	// Add component to objectID
	// Remove objectID
	// Remove component from objectID
	// Get signature by objectID
};