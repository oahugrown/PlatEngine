// RenderManager.h

#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H



#include "RenderManagerInterface.h"
#include "../GraphicsFactory.h"


const extern int k_windowHeight;
const extern int k_windowWidth;


class RenderQueue;
#include <vector>
class GameObject;
class RenderManager : public RenderManagerInterface
{
private:

	
	RenderQueue* m_pRenderQueue;
public:
	RenderManager();
	virtual ~RenderManager();
	// If a graphics type has been set, then run the start up by opening the window
	// Initialize what sprite type to use and render
	virtual void StartUp() override;
	// Clean up the renderManager for engine shut down
	virtual void ShutDown() override;
	// DrawSprites.
	virtual void DrawSprites(const Camera* camera) override;

	bool AddGameObjectToRender(GameObject* pRenderer);
	RenderQueue* GetRenderQueue() const { return m_pRenderQueue; };
};

#endif // RENDERMANAGER_H