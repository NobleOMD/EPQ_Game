#pragma once
#include "ecs/entityComponentSystem.hpp"
#include "components.hpp"

void registerComponents();

inline Group entities;

inline Group drawnObjects; // Requires Texture and Position components
void drawECS();
