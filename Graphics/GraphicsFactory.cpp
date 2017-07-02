// GraphicsFactory.cpp

#define USE_SDL

#include "GraphicsFactory.h"
#include "Macros.h"
#include "../Graphics/SDL/SDL.h"
#include "../Graphics/SDL/SDL_Sprite.h"

GraphicsFactory::GraphicsFactory()
	: m_pGraphicsRender(nullptr)
{
	//
}

GraphicsFactory::~GraphicsFactory()
{
	SAFE_DELETE(m_pGraphicsRender);
}


GraphicsRenderer* GraphicsFactory::GetGraphics()
{
#ifdef USE_SDL
	return GetSDL();
#else
    return nullptr;
#endif
}

GraphicsRenderer* GraphicsFactory::GetSDL()
{ 
	if (m_pGraphicsRender == nullptr)
	{
		m_pGraphicsRender = new SDL();
	}
	return m_pGraphicsRender;
};
