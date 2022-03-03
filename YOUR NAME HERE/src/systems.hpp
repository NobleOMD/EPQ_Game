#pragma once
#include <include/raylib-cpp.hpp>

#include "ecs/entityComponentSystem.hpp"
#include "components.hpp"

inline Group entities;		// All objectID's

inline Group drawnObjects;	// Requires Texture and Position components
void drawTextured();				// Draws all objects within above group

inline Group moveableObjects;
void move(ObjectID objectID, raylib::Vector2 translation);

inline Group playerInput;
void handlePlayerInput();
