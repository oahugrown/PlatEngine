// RenderComponent.h

#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H
#include "Component.h"
#include "Macros.h"

class Sprite;

class RenderComponent : public Component
{
private:
	const char* m_pFileName;
	Sprite* m_pSprite;

public:
	RenderComponent();
	~RenderComponent();
	// TODO: these needs to be private with setters/getters
	float m_w, m_h, m_x, m_y;
	float m_textureX, m_textureY;

	// Getters/Setters
	virtual void SetFileName(const char* pName);
	virtual const char* GetFileName() const { return m_pFileName; };
	virtual Sprite* GetSprite() const { return m_pSprite; };
};

#endif // !RENDERCOMPONENT_H