// RenderComponent.cpp

#include "RenderComponent.h"
#include "../../Graphics/Sprite.h"
#include "../../Graphics/SDL/SDL_Sprite.h"

RenderComponent::RenderComponent()
	: m_pSprite(nullptr)
	, m_y(0)
	, m_x(0)
	, m_h(0)
	, m_w(0)
	, m_textureX(0)
	, m_textureY(0)
{
	m_pSprite = new SDL_Sprite(this);
};

RenderComponent::~RenderComponent()
{
	SAFE_DELETE(m_pSprite);
}

void RenderComponent::SetFileName(const char* pName)
{
	m_pFileName = pName; 
	m_pSprite->SetFile(pName);
}

