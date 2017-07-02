// PlatEngine.h

#ifndef PLATENGINE_H
#define PLATENGINE_H

#ifdef PLATENGINE_EXPORTS
#define PLATENGINE_API __declspec(dllimport) 
#else
#define PLATENGINE_API __declspec(dllexport) 
#endif

class RenderManagerInterface;
class GameManager;

// This class is responsible for initial start up and shut down of core systems
class PlatEngine
{
private:
	static PlatEngine* m_pEngine;

	RenderManagerInterface* m_pRenderManager;
	GameManager* m_pGameManager;


public:
	PLATENGINE_API PlatEngine();
	~PlatEngine();

	// Obtain a single instance of PlatEngine
	static PLATENGINE_API PlatEngine* GetEngine();
	// Spin up PlatEngine and its systems
	void PLATENGINE_API StartEngine();
	// Cleanup and close down the engine
	void PLATENGINE_API ShutDownPlatEngine();

	// Manager Getters
	RenderManagerInterface* GetRenderManager() const { return m_pRenderManager; };
	GameManager* GetGameManager() const { return m_pGameManager; };

};

#endif //PLATENGINE_H