// PhysicsManager.cpp
#include "PhysicsManager.h"
#include "../GameObject/GameObjectComponents/RigidBodyComponent.h"
#include "Box2D.h"
#include "Time.h"

const float k_updateInterval = 1 / 60.0f;
const double k_secondsPerUpdate = 0.1f;
const int32 k_velocityIterations = 6;
const int32 k_positionIterations = 1;

PhysicsManager* PhysicsManager::s_pInstance;
PhysicsManager* PhysicsManager::GetPhysicsManager()
{
	if (!s_pInstance)
		s_pInstance = new PhysicsManager();

	return s_pInstance;
}

PhysicsManager::PhysicsManager()
	: m_accumulator(0)
{
	b2Vec2 gravity(0.0f, 10 / k_pixelsPerMeter);
	m_world = new b2World(gravity);
}

void PhysicsManager::SimulatePhysics()
{
	// If there are no bodies to simulate physics than bail
	if (m_world->GetBodyCount() == 0)
		return;

	m_accumulator += g_deltaTime;

	if (m_accumulator >= k_updateInterval)
	{
		m_world->Step(k_updateInterval, k_velocityIterations, k_positionIterations);
		m_accumulator -= k_updateInterval;
	}

	for (auto it : s_pAllRigidBodiesInWorld)
	{
		it->UpdatePosition();
	}
}


void PhysicsManager::AddRigidBodyToWorld(RigidBodyComponent* pNewRigidBody)
{
	if (!pNewRigidBody)
		return;
	s_pAllRigidBodiesInWorld.push_back(pNewRigidBody);
}