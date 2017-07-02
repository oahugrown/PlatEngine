// RenderQueue.h

#ifndef RENDERQUEUE_H
#define RENDERQUEUE_H

#include "../Sprite.h"
#include "../GameObject/GameObjectComponents/RenderComponent.h"
#include "../GameObject/GameObject.h"
#include <vector>
class RenderQueue
{
private:
	// TODO: Change this into a priority queue!
	std::vector<RenderComponent*> m_tiles;
	std::vector<GameObject*> m_gameObjects;
public:
	RenderQueue(){};
	~RenderQueue();
	
	// The following returns true if successful
	// Lets the renderer know what gameObjects to render
	bool AddToGameObjectsQueue(GameObject* pGameObject);
	// Removes renderer components that no longer need to be rendered.
	bool RemoveFromQueue(RenderComponent* pRenderer);
	// Set's the background tiles to be drawn in the window.
	void SetTiles(const std::vector<RenderComponent*> &tiles) { m_tiles = tiles; };

	// Getters/Setters
	const std::vector<RenderComponent*> &GetTiles(){ return m_tiles; };
	const std::vector<GameObject*> &GetGameObjects() { return m_gameObjects; };
};

#endif //!RENDERQUEUE_H