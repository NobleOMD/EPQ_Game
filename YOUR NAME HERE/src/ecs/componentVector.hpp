#include <unordered_map>
#include <vector>
#include <cassert>

#include "types.hpp"

/// Base class that we can cast to the correct type
class BaseContainer {
public:
	// Remove object virtual function so we don't need to cast to type to remove objects
	virtual void removeObject(ObjectID objectID) = 0;
};

/// ComponentVector stores and components of template type, components can be fetched by their objectID
template <typename Component>
class ComponentVector: public BaseContainer {
public:
	std::vector<Component> components; // The storage location for all the components

	/// Add a component to the component vector
	void add(Component component) {
		objectID_index[component.objectID] = components.size(); // Get the index that this object is created at
		components.push_back(component);
	}

	/// Remove a component by objectID
	void remove(ObjectID objectID) {
		assert(components.size() != 0 && "No components in vector to remove.");

		const size_t index = objectID_index[objectID];		// Get the index of the component to be removed
		objectID_index.erase(objectID);						// Remove the entry in the | objectID : index | map

		components[index] = components.back();				// Replace the component to be removed with a copy of the last element in the vector
		objectID_index[components[index].objectID] = index; // Update the map of | objectID : index | with the new position of the last element

		components.pop_back();								// Remove the last element that had been duplicated
	}

	/// Check for object and remove it if it exists.
	void removeObject(ObjectID objectID) override {
		if (objectID_index.find(objectID) != objectID_index.end()) {
			remove(objectID);
		}
	}

	/// Get a component by objectID
	Component &get(ObjectID objectID) {
		size_t index = objectID_index[objectID];	// Get the index of the component by objectID.
		return components[index];
	}

private:
	std::unordered_map<ObjectID, size_t> objectID_index;	// A map from the object ids of components to their position in the vector.
};
