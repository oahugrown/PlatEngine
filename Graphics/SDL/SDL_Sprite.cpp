#include "SDL_Sprite.h"

#include "Macros.h"
#include <SDL.h>
#include <SDL_image.h>
#include "../SDL/SDL.h"

SDL_Sprite::SDL_Sprite(RenderComponent* pRenderOwner)
	: m_pRenderOwner(nullptr)
	, m_pTexture(nullptr)
	, m_width(0)
	, m_height(0)
	, m_pRenderer(nullptr)
	, m_pSurface(nullptr)
	, m_pFilename()
{
	m_pRenderOwner = pRenderOwner;

	//Ask the engine what renderer is being used.
	m_pRenderer = SDL::GetRenderer();
}


SDL_Sprite::~SDL_Sprite()
{
	SDL_FreeSurface(m_pSurface);
	SDL_DestroyTexture(m_pTexture);
}

bool SDL_Sprite::DrawSprite(float x, float y, float w, float h, float tX, float tY)
{		
	if (m_pTexture == nullptr || m_pSurface == nullptr)
	{
		
		if (!LoadImage())
		{
//#if  DEBUG // Renders the Objects outline

			SDL_Rect outlineRect = { (int)x, (int)y, (int)w, (int)h};
			SDL_SetRenderDrawColor(m_pRenderer, 0xFF, 0x00, 0x00, 0xFF);
			SDL_RenderDrawRect(m_pRenderer, &outlineRect);

//#endif // DEBUG
			return false;
		}
	}
#if	DEBUG // Renders the Objects outline

	SDL_Rect outlineRect = { (int)x, (int)y, (int)w, (int)h };
	SDL_SetRenderDrawColor(m_pRenderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderDrawRect(m_pRenderer, &outlineRect);

#endif // DEBUG

	// If an image loaded correctly, then draw it
	SDL_Rect* textureRect = LoadClip((int)tX, (int)tY, (int)w, (int)h);
	SDL_Rect* screenTextureRect = LoadClip((int)x, (int)y, (int)w, (int)h);

	SDL_RenderCopy(m_pRenderer, m_pTexture, textureRect, screenTextureRect);

	SAFE_DELETE(textureRect);
	SAFE_DELETE(screenTextureRect);
	return true;
}

SDL_Rect* SDL_Sprite::LoadClip(int x, int y, int w, int h)
{
	SDL_Rect* rect = new SDL_Rect();

	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;

	return rect;
}

bool SDL_Sprite::LoadImage()
{
	if (!m_pFilename)
		return false;

	// Setting up the surface by filename
	m_pSurface = IMG_LoadPNG_RW(SDL_RWFromFile(m_pFilename, "rb"));
	if (m_pSurface == nullptr)
	{
		SDL_Log("%s", IMG_GetError());
		return nullptr;
	}

	// Now that we have the surface, set up the texture
	m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, m_pSurface);
	if (m_pTexture == nullptr)
	{
		SDL_Log("Failed to load pTexture %s\n", m_pFilename);
		return false;
	}

	return true;
}

void SDL_Sprite::SetFile(const char* pFile = nullptr)
{
	m_pFilename = pFile;
}