#include "ComponentManager.h"

#include "../GameObject/GameObjectComponents/TransformComponent.h"
#include "../GameObject/GameObjectComponents/RenderComponent.h"

#include "Macros.h"

ComponentManager::ComponentManager()
{
	m_pComponents[k_RendererComponent] = nullptr;
	m_pComponents[k_TransformComponent] = nullptr;
}


ComponentManager::~ComponentManager()
{
	// Free attached components
	for (auto it = m_pComponents.begin(); it != m_pComponents.end(); ++it)
	{
		delete(it->second);
		it->second = nullptr;
	}
}


// Attaches a NEW component to the gameObject.  It will NOT create and attach
// the component if one already exists.
void ComponentManager::AttachComponent(ComponentType componentType)
{
	if (m_pComponents[componentType] != nullptr)
	{
		LOG("ERROR:  GameObject cannot have more than one of the same component type.");
		return;
	}

	if (componentType == k_RendererComponent)
		m_pComponents[componentType] = new RenderComponent();

	else if (componentType == k_TransformComponent)
		m_pComponents[componentType] = new TransformComponent(0, 0);

}

void ComponentManager::RemoveComponent(ComponentType componentType)
{
	delete m_pComponents[componentType];
	m_pComponents[componentType] = nullptr;
}

void ComponentManager::SetTextureFile(char* pFileName)
{
	m_pComponents[k_RendererComponent]->SetFileName(pFileName);
}

void ComponentManager::DrawTexture()
{
	m_pComponents[k_RendererComponent]->GetSprite()->Draw();
}
