#include "GameManager.h"
#include "Macros.h"

#include "../Graphics/Rendering/RenderManagerInterface.h"
#include "../Core/PlatEngine.h"
#include "../Physics/PhysicsManager.h"
#include "../Input/EventPoll.h"
#include "World.h"

GameManager::GameManager()
	: m_running(true)
	, m_pRenderManager(nullptr)
	, m_pPhysicsManager(nullptr)
	, m_pWorld(nullptr)
	, m_pEventPoll(nullptr)
{
	m_pPhysicsManager = PhysicsManager::GetPhysicsManager();
}

GameManager::~GameManager()
{
	SAFE_DELETE(m_pWorld);
}

void GameManager::Run()
{
	// Make sure our managers have been cached.
	if (!m_pPhysicsManager)
		PhysicsManager::GetPhysicsManager();

	if (!m_pRenderManager)
		m_pRenderManager = PlatEngine::GetEngine()->GetRenderManager();

	if (!m_pEventPoll)
		m_pEventPoll = new EventPoll(m_pRenderManager->GetGraphicsFactory());

	// Main loop!
	// Simimulate physics, world updates, and render as long as our world remains valid.
	while (m_running)
	{
		if (m_pWorld)
		{
			// Simulate the physics
			m_pPhysicsManager->SimulatePhysics();

			// update the world
			m_pWorld->Update();

			// render the world
			m_pRenderManager->DrawSprites(m_pWorld->GetCamera());
		}
		// get key events
		m_running = m_pEventPoll->RunEventPoll();
	}

	// Our game is no long running, so PlatEngine will shut be shutting down
	PlatEngine::GetEngine()->ShutDownPlatEngine();
};