#include "ComponentObject.h"

#include "TransformComponent.h"
#include "RenderComponent.h"
#include "RigidBodyComponent.h"

#include "Macros.h"

ComponentObject::ComponentObject()
{
	m_pComponents[ComponentType::k_RendererComponent] = nullptr;
	m_pComponents[ComponentType::k_TransformComponent] = nullptr;
}


ComponentObject::~ComponentObject()
{
	// Free attached components
	for (auto it = m_pComponents.begin(); it != m_pComponents.end(); ++it)
	{
		SAFE_DELETE(it->second);
	}
}


// Attaches a NEW component to the gameObject.  It will NOT create and attach
// the component if one already exists.
void ComponentObject::AttachComponent(ComponentType componentType)
{
	if (m_pComponents[componentType] != nullptr)
	{
		// for now only allow one component of the same type....
		LOG("ERROR:  GameObject cannot have more than one of the same component type.");
		return;
	}

	// Setting up our new component whatever it may be
	if (componentType == ComponentType::k_RendererComponent)
		m_pComponents[componentType] = new RenderComponent();

	else if (componentType == ComponentType::k_TransformComponent)
		m_pComponents[componentType] = new TransformComponent(0, 0);

	else if (componentType == ComponentType::k_RigidBodyComponent)
		m_pComponents[componentType] = new RigidBodyComponent();
}

void ComponentObject::RemoveComponent(ComponentType componentType)
{
	// Make sure that this componentObject has the componentType attached to it before removal.
	if (m_pComponents[componentType] == nullptr)
	{
		LOG("ERROR: This ComponentObject doesn't have this componentType currently registered")
			return;
	}

	SAFE_DELETE(m_pComponents[componentType]);
	m_pComponents[componentType] = nullptr;
}
