// PlatEngine.cpp
#include "PlatEngine.h"
#include "MACROS.h"


// Include all other managers that need to startup/shutdown
#include "../Graphics/Rendering/RenderManagerInterface.h"
#include "../Graphics/Rendering/RenderManager.h"
#include "../Core/GameManager.h"

PlatEngine* PlatEngine::m_pEngine = nullptr;

PlatEngine::PlatEngine()
	: m_pGameManager(nullptr)
	, m_pRenderManager(nullptr)
{
	//
}

PlatEngine::~PlatEngine()
{
	SAFE_DELETE(m_pGameManager);
	SAFE_DELETE(m_pRenderManager);
}

PlatEngine* PlatEngine::GetEngine() 
{
	if (m_pEngine == nullptr)
		m_pEngine = new PlatEngine();

	return m_pEngine;
};

// --------------------------------------------------------------------------------------------------------------------
// Start up
// --------------------------------------------------------------------------------------------------------------------
void PlatEngine::StartEngine()
{
	m_pRenderManager = new RenderManager();

	// Start up the renderer
	m_pRenderManager->StartUp();
}

void PlatEngine::ShutDownPlatEngine()
{
    if (m_pRenderManager)
    {
		// Closing our window
	    m_pRenderManager->ShutDown();
    }

	SAFE_DELETE(m_pEngine);
};

// --------------------------------------------------------------------------------------------------------------------
// Manager getters
// --------------------------------------------------------------------------------------------------------------------