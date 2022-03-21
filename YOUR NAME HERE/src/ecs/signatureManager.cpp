#include "signatureManager.hpp"
/// Add objectID to | ObjectID : Signature | map

void SignatureManager::newObjectSignature(ObjectID objectID) {
	Signature newSignature = 0b0000;
	objectID_signature[objectID] = newSignature;
}

/// Remove objectID from | ObjectID : Signature | map

void SignatureManager::removeObject(ObjectID objectID) {
	objectID_signature.erase(objectID);
}

/// Get the signature of component by type

Signature SignatureManager::getComponentSignature(std::type_index typeName) {
	return componentSignatures[typeName];
}
