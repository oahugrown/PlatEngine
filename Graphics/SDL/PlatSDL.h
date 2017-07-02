// SDL.h

#ifndef SDL_H
#define SDL_H

#include "../GraphicsRenderer.h"
#include <SDL.h>
#include <vector>
class Input;
class Camera;
class RenderComponent;
class TransformComponent;

class SDL : public GraphicsRenderer
{
private:
	static int m_windowWidth;
	static int m_windowHeight;
	static SDL_Window* s_pSDLWindow;
	static SDL_Renderer* s_pSDLRenderer;

	Uint32 m_oldTime, m_currentTime;
	std::vector<RenderComponent*> m_gameObjectRenderComponents;
	std::vector<TransformComponent*> m_gameObjectTransformComponents;

public:
	SDL();
	virtual void OpenWindow(int windowWidth, int windowHeight) override;
	virtual void CloseWindow() override;
	virtual bool RunPollEvent() override;
	virtual void Render(RenderQueue& queue, const Camera* pCamera) override;

	static SDL_Renderer* GetRenderer(){ return s_pSDLRenderer; };
	static void SetRenderer();
	static void SetWindow();
};

#endif // SDL_H