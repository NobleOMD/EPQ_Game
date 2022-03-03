#pragma once
#include "ecs/entityComponentSystem.hpp"
#include "components.hpp"

void registerComponents();	// Setup all components with the component manager

inline Group entities;		// All objectID's

inline Group drawnObjects;	// Requires Texture and Position components
void draw();				// Draws all objects within above group
