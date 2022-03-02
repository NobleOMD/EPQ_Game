#include <unordered_map>
#include <vector>
#include <cassert>

#include "types.hpp"

extern ObjectID;

class BaseContainer {}; // Base class that we can cast to the correct type

template <typename Component>
class ComponentVector: public BaseContainer {
public:
	std::vector<Component> components;

	void add(Component component) {
		const size_t index = aliveComponents;
		components.push_back(component);
		objectID_index[component.objectID] = aliveComponents;
		aliveComponents++;
	}

	void remove(ObjectID objectID) {
		assert(aliveComponents != 0);

		const size_t index = objectID_index[objectID];
		components.erase(components.begin() + index);
		objectID_index.erase(objectID);

		aliveComponents--;
	}

	Component &get(ObjectID objectID) {
		return components[objectID_index[objectID]];
	}

private:
	size_t aliveComponents = 0;
	std::unordered_map<ObjectID, size_t> objectID_index;
};
