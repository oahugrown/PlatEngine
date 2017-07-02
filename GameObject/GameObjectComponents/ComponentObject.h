// ComponentManager.h

#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#ifdef PLATENGINE_EXPORTS
#define COMPONENTOBJECT_H __declspec(dllimport) 
#else
#define COMPONENTOBJECT_H __declspec(dllexport) 
#endif

#include"Component.h"
#include <unordered_map>

// List of all component types that PlatEngine currently supports
enum class ComponentType
{
	k_TransformComponent,
	k_RendererComponent,
	k_RigidBodyComponent
};

class Component;

// This class is responsible for managing all components to its owner.
// It will create and store the components that its owner owns.
// This is the base class to inherit to if you wish to create a base object
// that supports components.
class ComponentObject
{
private:
	std::unordered_map<ComponentType, Component*> m_pComponents;

public:
	COMPONENTOBJECT_H ComponentObject();
	COMPONENTOBJECT_H ~ComponentObject();

	// Returns NULLPTR if the componentType does not exist on the gameObject 
	Component* GetComponent(ComponentType componentType) { return m_pComponents[componentType]; };
	// Attaches a new component to this object IF and ONLY IF that component doesn't already exist on the object.
	// PlatEngine currently doesn't support multiple components of the same type.
	void COMPONENTOBJECT_H AttachComponent(ComponentType componentType);
	// PlatEngine's process of removing a component attached to it.
	// It will delete the component, and unregister it from the map of components it references.
	void COMPONENTOBJECT_H RemoveComponent(ComponentType componentType);

};

#endif // !COMPONENTMANAGER_H