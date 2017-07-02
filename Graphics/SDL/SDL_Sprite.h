// SDL_Sprite.h

#ifndef SDL_SPRITE_H
#define SDL_SPRITE_H


#include "../Sprite.h"
#include <SDL_image.h>

class RenderComponent;

class SDL_Sprite : public Sprite
{
private:
	RenderComponent* m_pRenderOwner;
	SDL_Texture* m_pTexture;
	int m_width, m_height;
	SDL_Renderer* m_pRenderer;
	SDL_Surface *m_pSurface;
	const char* m_pFilename;

public:
	SDL_Sprite(RenderComponent* pOwner);
	~SDL_Sprite();


	SDL_Rect* LoadClip(int x, int y, int w, int h);

	virtual bool Draw(int x, int y, int w, int h) override;
	virtual bool DrawSprite(float u, float v, float u2, float v2, float tX, float tY) override;
	virtual bool LoadImage() override;
	virtual void SetFile(const char* pfile) override;

};

#endif // !SDL_SPRITE_H