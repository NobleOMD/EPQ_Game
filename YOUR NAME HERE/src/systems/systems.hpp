#pragma once
#include <include/raylib-cpp.hpp>

#include "../ecs/ECSManager.hpp"
#include "../components/components.hpp"

#include "drawingSystems.hpp"
#include "healthSystems.hpp"
#include "playerInput.hpp"
#include "movementSystems.hpp"
#include "collisionSystems.hpp"
#include "damageSystems.hpp"

namespace systems
{
	void registerSystems();
	void updateSystems();
	void drawSystems();
}
