// GameObject.cpp

#include "GameObject.h"
#include "Macros.h"


GameObject::GameObject()
	: m_isTickable(false)
{
	// all gameObjects will have a transform component
	AttachComponent(ComponentType::k_TransformComponent);
	AttachComponent(ComponentType::k_RendererComponent);
}
