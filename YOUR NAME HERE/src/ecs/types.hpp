#pragma once
#include <cstdint>
#include <set>

using ObjectID = uint16_t;			// The type used for ObjectID changing this increases the max number of objects
using Group = std::set<ObjectID>;	// A group is just a set of ObjectID's that can be iterated over. A set is used as ObjectID's should be unique