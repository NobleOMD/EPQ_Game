#pragma once
#include <include/raylib-cpp.hpp>

#include "drawingSystems.hpp"
#include "healthSystems.hpp"
#include "playerInput.hpp"
#include "movementSystems.hpp"
#include "collisionSystems.hpp"
#include "damageSystems.hpp"
#include "AImovement.hpp"

namespace systems
{
	void registerSystems();
	void updateSystems();
	void drawSystems();
}
