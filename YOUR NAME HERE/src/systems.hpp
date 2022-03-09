#pragma once
#include <include/raylib-cpp.hpp>
#include <vector>

#include "ecs/ECSManager.hpp"
#include "components.hpp"

namespace systems
{
	void registerSystems();
	void addToGroups(ObjectID objectID, std::vector<Group *> groups);
	bool hasComponents(ObjectID objectID, Signature requiredComponents);

	inline std::vector<ObjectID> removeQueue;

	// Drawing Systems
	//---------------------------------------------------------------------------------
	inline Group drawTextured;
	void drawTextures();	// Draws all objects within above group with their texture

	inline Group drawDebugging;
	void drawDebug();		// Draws all objects within above group with a blue outline

	inline Group drawAnimated;
	void tickAnimations();
	//---------------------------------------------------------------------------------

	// Movement
	//---------------------------------------------------------------------------------
	inline Group moveableObjects;
	void move(ObjectID objectID, raylib::Vector2 translation);
	//---------------------------------------------------------------------------------

	// Input
	//---------------------------------------------------------------------------------
	inline Group player;
	inline Group enemies;
	void handlePlayerInput();
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
