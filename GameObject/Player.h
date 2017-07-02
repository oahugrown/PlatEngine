// Player.h

#ifndef PLAYER_H
#define PLAYER_H

#ifdef PLATENGINE_EXPORTS
#define PLAYER_API __declspec(dllimport) 
#else
#define PLAYER_API __declspec(dllexport) 
#endif

#include "GameObject.h"

class World;
class InputHandler;
class RigidBodyComponent;
class TransformComponent;

// TODO: Make this an interface and pull the data out into game.exe!
class Player : public GameObject
{
protected:
	RigidBodyComponent* m_pRigidBody;
	TransformComponent* m_pTransform;
	InputHandler* m_pInputHandler;
	float m_moveSpeed;
	float m_jumpForce;

public:
	PLAYER_API Player();
	virtual PLAYER_API ~Player();
	// Initializing player properties.
	virtual void PLAYER_API InitializePlayer(World* pWorld) = 0;

};

#endif // !PLAYER_H
