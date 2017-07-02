// ComponentManager.h

#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include"../GameObject/GameObjectComponents/Component.h"
#include <unordered_map>

enum ComponentType
{
	k_TransformComponent,
	k_RendererComponent,
};

class Component;

/*  THIS CLASS IS RESPONSIBLE FOR MANAGING ALL COMPONENTS TO ITS OWNER.      */
/*  IT WILL CREATE AND STORE THE COMPONENTS THAT ITS OWNER OWNS.		     */
class ComponentManager
{
private:
	std::unordered_map<ComponentType, Component*> m_pComponents;

public:
	ComponentManager();
	~ComponentManager();
	// Returns NULLPTR if the componentType does not exist on the gameObject 
	Component* GetComponent(ComponentType componentType) { return m_pComponents[componentType]; };
	void AttachComponent(ComponentType componentType);
	void RemoveComponent(ComponentType componentType);

	// Renderer component management
	void SetTextureFile(char* pFileName);
	void DrawTexture();
};

#endif // !COMPONENTMANAGER_H