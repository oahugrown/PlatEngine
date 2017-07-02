#include "RenderQueue.h"

#include "Macros.h"

RenderQueue::~RenderQueue()
{
	for (auto it : m_tiles)
	{
		SAFE_DELETE(it);
	}
}

bool RenderQueue::AddToGameObjectsQueue(GameObject* pGameObject)
{
	if (pGameObject)
	{
		m_gameObjects.push_back(pGameObject);
		return true;
	}
	return false;
}

// TODO: Finish remove from queue
bool RenderQueue::RemoveFromQueue(RenderComponent*)
{
	return true;
}