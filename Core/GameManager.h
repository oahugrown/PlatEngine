// GameManager.h

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#ifdef PLATENGINE_EXPORTS
#define PLATENGINE_API __declspec(dllimport) 
#else
#define PLATENGINE_API __declspec(dllexport) 
#endif

#include <vector>

class PhysicsManager;
class RenderManagerInterface;
class World;
class EventPoll;

class GameManager
{
protected:
	// The world the GameManager is running
	World* m_pWorld;

private:
	// returns false upon user wanting to quit/esc out of the program
	bool m_running;
	EventPoll* m_pEventPoll;
	RenderManagerInterface* m_pRenderManager;
	PhysicsManager* m_pPhysicsManager;

public:
	PLATENGINE_API GameManager();
	virtual PLATENGINE_API ~GameManager();
	// This is how PlatEngine knows when to run the game.  Call it in you're Game.exe
	// AFTER loading and initializing the game world.
	virtual PLATENGINE_API void Run();
};

#endif //GAMEMANAGER_H