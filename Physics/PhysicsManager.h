// PhysicsManager.h

// TODO: Turn this into Box2DPhysics, and create a PhysicsManagerInterface.

#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

const static float k_pixelsPerMeter = 1;

#include <vector>
class RigidBodyComponent;
class b2World;
class PhysicsManager
{
	static PhysicsManager* s_pInstance;

public:
	PhysicsManager();

	b2World* GetWorld() { return m_world; };
	static PhysicsManager* GetPhysicsManager();
	void SimulatePhysics();
	void AddRigidBodyToWorld(RigidBodyComponent* pNewRigidBody);


private:
	std::vector<RigidBodyComponent*> s_pAllRigidBodiesInWorld;
	double m_accumulator;
	b2World* m_world;

	
};

#endif // !PHYSICSMANAGER_H
