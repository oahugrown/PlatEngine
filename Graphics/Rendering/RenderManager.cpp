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
	GraphicsRenderer &m_renderer = *m_pGraphics->GetGraphics();
	if (&m_renderer)
		m_renderer.OpenWindow(k_windowWidth, k_windowHeight);
};

// Shut down the renderer by closing the program window 
void RenderManager::ShutDown()
{
	GraphicsRenderer &m_renderer = *m_pGraphics->GetGraphics();
	if (&m_renderer)
		m_renderer.CloseWindow();
};

// Drawing all the sprites
void RenderManager::DrawSprites( const Camera* camera)
{
	GraphicsRenderer &m_renderer = *m_pGraphics->GetGraphics();
	if (&m_renderer)
		m_renderer.Render(*m_pRenderQueue, camera);
}

bool RenderManager::AddGameObjectToRender(GameObject* pGameObject)
{
	return m_pRenderQueue->AddToGameObjectsQueue(pGameObject);
}
