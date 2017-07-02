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

bool SDL_Sprite::Draw(int posX, int posY, int w, int h)
{
	if (m_pTexture == nullptr || m_pSurface == nullptr)
	{
		if (!LoadImage())
		{
			SDL_Rect outlineRect = { posX, posY, w, h };
			SDL_SetRenderDrawColor(m_pRenderer, 0xFF, 0x00, 0x00, 0xFF);
			SDL_RenderDrawRect(m_pRenderer, &outlineRect);
			return false;
		}
	}
	SDL_Rect outlineRect = { posX, posY, w, h };
	SDL_SetRenderDrawColor(m_pRenderer, 0xFF, 0xff, 0x00, 0xFF);
	SDL_RenderDrawRect(m_pRenderer, &outlineRect);

	SDL_Rect textureRect;
	SDL_Rect screenTextureRect;
	// Getting Texture's bounds for setting texture rect
	int* pWidth = new int (0);
	int* pHeight = new int (0);
	if (SDL_QueryTexture(m_pTexture, nullptr, nullptr, pWidth, pHeight) < 0)
	{
		SDL_Log("SDL_Query failed in DrawTexture!\n");
	}

	// setting up the textures rect
	textureRect.x = 0;
	textureRect.y = 0;
	textureRect.w = *pWidth;
	textureRect.h = *pHeight;

	// Positioning the render at the gameObject's position
	screenTextureRect.x = posX;
	screenTextureRect.y = posY;
	screenTextureRect.w = *pWidth;
	screenTextureRect.h = *pHeight;

	m_width = *pWidth;
	m_height = *pHeight;

	//SDL_Log("%d", posY);
	if (m_pTexture == nullptr)
		return false;
	if (SDL_RenderCopy(m_pRenderer, m_pTexture, &textureRect, &screenTextureRect) < 0)
	{
		SDL_Log("RenderCopy failed for %s", m_pTexture);
		return false;
	}

	SAFE_DELETE(pHeight);
	SAFE_DELETE(pWidth);
	
	return true;
}

bool SDL_Sprite::DrawSprite(float x, float y, float w, float h, float tX, float tY)
{		
	if (m_pTexture == nullptr || m_pSurface == nullptr)
	{
		if (!LoadImage())
		{
			// TODO: Turn this into a debugging thing.
			SDL_Rect outlineRect = { (int)x, (int)y, (int)w, (int)h};
			SDL_SetRenderDrawColor(m_pRenderer, 0xFF, 0x00, 0x00, 0xFF);
			SDL_RenderDrawRect(m_pRenderer, &outlineRect);
			return false;
		}
	}

	SDL_Rect* textureRect = LoadClip((int)tX, (int)tY, (int)w, (int)h);
	SDL_Rect* screenTextureRect = LoadClip((int)x, (int)y, (int)w, (int)h);

	SDL_Rect outlineRect = { (int)x, (int)y, (int)w, (int)h };
	SDL_SetRenderDrawColor(m_pRenderer, 0xFF, 0xff, 0x00, 0xFF);
	SDL_RenderDrawRect(m_pRenderer, &outlineRect);

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