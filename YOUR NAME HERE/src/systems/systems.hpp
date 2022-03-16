#pragma once
#include <include/raylib-cpp.hpp>

#include "../ecs/ECSManager.hpp"
#include "../components/components.hpp"

#include "drawingSystems.hpp"
#include "healthSystem.hpp"
#include "playerInput.hpp"

namespace systems
{
	void registerSystems();
	void addToGroups(ObjectID objectID, std::vector<Group *> groups);
	bool hasComponents(ObjectID objectID, Signature requiredComponents);

	// Movement
	//---------------------------------------------------------------------------------
	inline Group moveableObjects;
	void move(ObjectID objectID, raylib::Vector2 translation);
	//---------------------------------------------------------------------------------

	// Collision
	//---------------------------------------------------------------------------------
	inline Group collisionObjects;
	ObjectID collisionCheck(ObjectID objectID, const Group &createObject);
	void move(ObjectID objectID, raylib::Vector2 translation, const Group &collisionObjects);

	inline Group damageObjects;
	void doDamage(DamageComponent &damageObject, const Group &collisionObjects);
	void handleDamage();
	//---------------------------------------------------------------------------------
}
