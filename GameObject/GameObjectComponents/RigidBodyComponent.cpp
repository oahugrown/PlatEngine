#include "RigidBodyComponent.h"

#include "TransformComponent.h"
#include "World.h"
#include "../Physics/PhysicsManager.h"


RigidBodyComponent::RigidBodyComponent()
	: m_hasGravity(false)
	, m_bodyDef()
	, m_body(nullptr)
	, m_dynamicBox()
	, m_fixtureDef()
	, m_pPhysicsManager(nullptr)
{
	//
}

void RigidBodyComponent::Initialize(World* pWorld, TransformComponent* pTransform, bool hasGravity = false)
{
	m_pTransformComponent = pTransform;
	m_hasGravity = hasGravity;
	m_gravityForce = pWorld->GetGravity();
	m_pPhysicsManager = PhysicsManager::GetPhysicsManager();
	
	// Post-Initialize, set up Box2D configuration on this rigidBody
	// and add the box2D body to the box2D world.
	InitializeBody();
	AddRigidBodyToWorld();
}

void RigidBodyComponent::InitializeBody()
{
	float posX = m_pTransformComponent->GetX();
	float posY = m_pTransformComponent->GetY();
	float width = m_pTransformComponent->GetWidth();
	float height = m_pTransformComponent->GetHeight();
		
	m_bodyDef.position.Set(posX / k_pixelsPerMeter, posY / k_pixelsPerMeter);
	m_bodyDef.userData = this;
	m_bodyDef.fixedRotation = true;

	// if the rigidBody should be affected by gravity, then the box2D type must be dynamic.
	if (m_hasGravity)
		m_bodyDef.type = b2_dynamicBody;

	// Box2D creates bodies by Box2D's world.  It shouldn't be created in any other way.
	m_body = m_pPhysicsManager->GetWorld()->CreateBody(&m_bodyDef);

	// Creating the shape (box)
	b2Vec2 centerPoint((float32)width / 2, (float32)height / 2);
	m_dynamicBox.SetAsBox((float32)width / 2, (float32)height / 2, centerPoint, 0);

	// Setting up the fixture information
	m_fixtureDef.shape = &m_dynamicBox;
	m_fixtureDef.density = 1.0f;
	m_fixtureDef.friction = 1.0f;

	// Create the fixture based off of if it's static or dynamic.
	if (m_hasGravity)
		m_body->CreateFixture(&m_fixtureDef);
	else
		m_body->CreateFixture(&m_dynamicBox, 1);
}

void RigidBodyComponent::AddRigidBodyToWorld()
{
	// Pushes this rigidBody component in a list to unsure after physics is simulated
	// all the rigidBody components get their positions update.
	// TODO: Refactor this so that only dynamic bodies get pushed to the list.
	m_pPhysicsManager->AddRigidBodyToWorld(this);
}

void RigidBodyComponent::UpdatePosition()
{
	// Getting box2d position and setting it in the transform position
	b2Vec2 position = m_body->GetPosition();
	m_pTransformComponent->SetX(position.x / k_pixelsPerMeter);
	m_pTransformComponent->SetY(position.y / k_pixelsPerMeter);
}

void RigidBodyComponent::SetLinearVelocity(float velocity, Direction dir)
{
	// Based off of the direction and velocity, it calls a Box2D method
	// to apply force to this rigidBody.
	// TODO: check if this rigidBody type is static or dynamic and bail if it's static
	b2Vec2 vel = m_body->GetLinearVelocity();
	if (dir == Direction::k_horizontal)
		vel.x = velocity;
	else
		vel.y = velocity;
	m_body->SetLinearVelocity(vel);
}

