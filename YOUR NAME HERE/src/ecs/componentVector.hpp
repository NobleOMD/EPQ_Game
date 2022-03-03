#include <unordered_map>
#include <vector>
#include <cassert>

#include "types.hpp"

class BaseContainer {}; // Base class that we can cast to the correct type

template <typename Component>
// ComponentVector stores and components of template type, components can be fetched by their objectID
class ComponentVector: public BaseContainer {
public:
	std::vector<Component> components; // The storage location for all the components

	void add(Component component) {
		objectID_index[component.objectID] = components.size(); // Get the index that this object is created at
		components.push_back(component);
	}

	void remove(ObjectID objectID) {
		assert(components.size() != 0 && "No components in vector to remove.");

		const size_t index = objectID_index[objectID];		// Get the index of the component to be removed
		objectID_index.erase(objectID);						// Remove the entry in the | objectID : index | map

		components[index] = components.back();				// Replace the component to be removed with a copy of the last element in the vector
		objectID_index[components[index].objectID] = index; // Update the map of | objectID : index | with the new position of the last element

		components.pop_back();								// Remove the last element that had been duplicated
	}

	Component &get(ObjectID objectID) {
		return components[objectID_index[objectID]];
	}

private:
	std::unordered_map<ObjectID, size_t> objectID_index;
};
