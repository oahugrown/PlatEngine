// GameObject.h

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "../GameObject/GameObjectComponents/ComponentObject.h"

class Component;
class GameObject : public ComponentObject
{
protected:
	bool m_isTickable;
	const char* m_pName;

public:
	GameObject();
	~GameObject(){};

	// Allow this tick function to be called when m_isTickable is set to true.
	virtual void Tick(){};

	// Getters/Setters
	virtual void SetName(const char* pName) { m_pName = pName; };
	const char* GetName() { return m_pName; };

};

#endif // !GAMEOBJECT_H