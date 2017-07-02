#include "RenderManager.h"
#include "RenderQueue.h"
#include "Macros.h"


const int k_windowHeight = 600;
const int k_windowWidth = 800;

// Upon construction of the RenderManager, a GraphicsFactory is created to
// determine which render layer to use.
RenderManager::RenderManager()
	: m_pRenderQueue(nullptr)
{
	m_pRenderQueue = new RenderQueue();
	m_pGraphics = new GraphicsFactory();
}

RenderManager::~RenderManager()
{
	SAFE_DELETE(m_pRenderQueue);
	SAFE_DELETE(m_pGraphics);
}


void RenderManager::StartUp()
{
	if (m_pGraphics->GetGraphics())
	{
		m_pGraphics->GetGraphics()->OpenWindow(k_windowWidth, k_windowHeight);
	}
};

// Shut down the renderer by closing the program window 
void RenderManager::ShutDown()
{
	if (m_pGraphics->GetGraphics())
	{
		m_pGraphics->GetGraphics()->CloseWindow();
	}
};

// Drawing all the sprites
void RenderManager::DrawSprites( const Camera* camera)
{
	if (m_pGraphics->GetGraphics())
	{
		m_pGraphics->GetGraphics()->Render(*m_pRenderQueue, camera);
	}
}

bool RenderManager::AddGameObjectToRender(GameObject* pGameObject)
{
	return m_pRenderQueue->AddToGameObjectsQueue(pGameObject);
}
