#pragma once
#include <cstdint>
#include <set>
#include <bitset>

using ObjectID = uint16_t;			// The type used for ObjectID changing this increases the max number of objects
using Group = std::set<ObjectID>;	// A group is just a set of ObjectID's that can be iterated over. A set is used as ObjectID's should be unique

struct BaseSystem {
	Group group;
	virtual void update() =0;
};

constexpr size_t MAX_COMPONENTS = 32;
using Signature = std::bitset<MAX_COMPONENTS>;