#pragma once
#include "types.hpp"
#include "componentManager.hpp"

inline ObjectID createdObjects = 0;			// The total number of created objects used to create unique objectID's
inline ComponentManager componentManager;	// Global component manager