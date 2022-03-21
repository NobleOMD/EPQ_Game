#pragma once
#include <cstdint>
#include <set>
#include <bitset>

using ObjectID = uint16_t;			// The type used for ObjectID changing this increases the max number of objects

constexpr size_t MAX_COMPONENTS = 32;

struct BaseComponent {
	ObjectID objectID;
};

using Signature = std::bitset<MAX_COMPONENTS>;
using Group = std::set<ObjectID>;	// A group is just a set of ObjectID's that can be iterated over. A set is used as ObjectID's should be unique

class BaseSystem {
public:
	Group group;
	virtual void update() = 0;
	void removeObject(ObjectID objectID);
};

class SystemGroup: public BaseSystem {
public:
	void update() override; // Remove the use of the update function for any derived class
};
