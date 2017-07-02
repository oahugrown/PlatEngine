// RigidBodyComponent.h

#ifndef RIGIDBODYCOMPONENT_H
#define RIGIDBODYCOMPONENT_H

#ifdef PLATENGINE_EXPORTS
#define RIGIDBODYCOMPONENT_API __declspec(dllimport) 
#else
#define RIGIDBODYCOMPONENT_API __declspec(dllexport) 
#endif

#include "Component.h"
#include "Box2D.h"

enum class Direction
{
	k_horizontal,
	k_vertical,
};

class World;
class TransformComponent;
class PhysicsManager;

// TODO: Make this a Box2DRigidBody, and give it a RigidBodyInterface
// TODO: Decouple this component from TransformComponent or maybe not todo?
class RigidBodyComponent : public Component
{
private:
	b2BodyDef m_bodyDef;
	b2Body* m_body;
	b2PolygonShape m_dynamicBox;
	b2FixtureDef m_fixtureDef;
	PhysicsManager* m_pPhysicsManager;
	bool m_hasGravity;

	float m_gravityForce;
	
	// The transform component that the rigidBody's owner has.
	TransformComponent* m_pTransformComponent;

	// Initializes the rigidBody component properties for box2D specifically.
	// This function is called post Initialize()
	void InitializeBody();
	// Box2D has one world, that has a bunch of bodies in that world.  This
	// method will add the box2D body attached to it, to that one world to simulate physics.
	void AddRigidBodyToWorld();

public:
	RigidBodyComponent();
	// Initializes the rigidBody properties and sets the parameterized data.
	void RIGIDBODYCOMPONENT_API Initialize(World* pWorld, TransformComponent* pTransform, bool hasGravity);
	// Since box2D only updates the position of the box2D body during physics simulation,
	// UpdatePosition is meant to translate the position of the box2D body, to the transform
	// component itself.
	void RIGIDBODYCOMPONENT_API UpdatePosition();
	// A super simple method that applies force to the object, if this rigidBody type
	// is set to dynamic.  If the component is set to static, this function will do nothing.
	void RIGIDBODYCOMPONENT_API SetLinearVelocity(float velocity, Direction dir);
};

#endif // !RIGIDBODYCOMPONENT_H