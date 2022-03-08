#pragma once
#include <include/raylib-cpp.hpp>
#include <vector>

#include "ecs/ECSManager.hpp"
#include "components.hpp"

namespace systems
{
	void addToGroups(ObjectID objectID, std::vector<Group *> groups);
	bool hasComponents(ObjectID objectID, Signature requiredComponents);

	// Drawing Systems
	//---------------------------------------------------------------------------------
	//inline Signature drawSignature = globalManager.createSignature( {typeid(PositionComponent), typeid(SizeComponent), typeid(TextureComponent)} );

	inline Group drawnObjects;
	void drawTextured();	// Draws all objects within above group with their texture

	inline Group drawDebugging;
	void drawDebug();		// Draws all objects within above group with a blue outline
	//---------------------------------------------------------------------------------

	// Movement
	//---------------------------------------------------------------------------------
	//inline Signature moveSignature = globalManager.createSignature( {typeid(PositionComponent), typeid(SizeComponent)} );

	inline Group moveableObjects;
	void move(ObjectID objectID, raylib::Vector2 translation);
	//---------------------------------------------------------------------------------

	// Input
	//---------------------------------------------------------------------------------
	inline Group playerInput;
	void handlePlayerInput();
	//---------------------------------------------------------------------------------

	// Collision
	//---------------------------------------------------------------------------------
	inline Group collisionObjects;
	ObjectID collisionCheck(ObjectID objectID, const Group &createObject);
	void move(ObjectID objectID, raylib::Vector2 translation, const Group &collisionObjects);
	//---------------------------------------------------------------------------------
}
