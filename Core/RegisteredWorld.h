// RegisteredWorld.h

#ifndef REGISTEREDWORLD_H
#define REGISTEREDWORLD_H

#include "../EventSystem/EventListener.h"
#include "../EventSystem/Event.h"
#include "World.h"
#include "Macros.h"

#ifdef PLATENGINE_EXPORTS
#define PLATENGINE_API __declspec(dllexport) 
#else
#define PLATENGINE_API __declspec(dllimport) 
#endif

// [Yvy] sorry this got a little messy in an effort to use my event system with world registration...

PLATENGINE_API World* g_pRegisteredWorld;

// This class will notify the game engine which world it should start up.
class RegisteredWorld : public EventListener
{

public:
	// We only want one instance of world registration.
	static RegisteredWorld* m_pInstance;

	static RegisteredWorld* GetRegisteredWorld()
	{
		if (!m_pInstance)
			m_pInstance = new RegisteredWorld();
		return m_pInstance;
	};

	void SetWorld(World* m_pWorld) { g_pRegisteredWorld = m_pWorld; };
	World* GetWorld() const { return g_pRegisteredWorld; };

	// If our registered world is valid, then PlatEngine will initialize the world
	virtual bool OnNotifySuccess() override
	{
		if (g_pRegisteredWorld)
		{
			g_pRegisteredWorld->Start();
			return true;
		}
		LOG("ERROR: World wasn't set properly, PlatEngine has nothing to run.");
		return false;
	};
};

RegisteredWorld* RegisteredWorld::m_pInstance = nullptr;

// The event that registered the world from the game into the PlatEngine
class WorldRegistration : public Event 
{
public:
	// Only one registration should exist
	static WorldRegistration* m_pInstance;

	static WorldRegistration* GetWorldRegistration()
	{
		if (!m_pInstance)
			m_pInstance = new WorldRegistration();
		return m_pInstance;
	}
};

WorldRegistration* WorldRegistration::m_pInstance;

#endif // !REGISTEREDWORLD_H