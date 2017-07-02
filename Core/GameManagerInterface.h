// GameManagerInterface.h

#ifndef GAMEMANAGERINTERFACE_H
#define GAMEMANAGERINTERFACE_H

#include "../Core/PlatEngine.h"
#include "Macros.h"
#include "World.h"
// class GameManagerInterface
// {
// protected:
// 	World m_world;
// 
// public:
// 	GameManagerInterface():m_world() {};
// 	virtual ~GameManagerInterface() {};
// 	virtual bool WorldSuccessfullyLoaded()
// 	{
// 		if (!&m_world)
// 		{
// 			LOG("ERROR: Failed to load the game world, PlatEngine has nothing to run.")
// 				return false;
// 		}
// 		m_world.Start();
// 		return true;
// 	}
// 	virtual void Run() = 0;
// };

#endif // GAMEMANAGERINTERFACE_H