#include "SDL.h"

#include "../Rendering/RenderQueue.h"
#include "../../Input/InputHandler.h"
#include "../../GameObject/GameObject.h"
#include "../../GameObject/GameObjectComponents/RenderComponent.h"
#include "../../GameObject/GameObjectComponents/TransformComponent.h"
#include "../Camera.h"
#include "Time.h"
#include "Macros.h"

SDL_Renderer* SDL::s_pSDLRenderer = nullptr;
SDL_Window* SDL::s_pSDLWindow = nullptr;
int SDL::m_windowWidth = 0;
int SDL::m_windowHeight = 0;
double g_deltaTime;

SDL::SDL()
	: m_oldTime(0)
	, m_currentTime(0)
{
	//
}

void SDL::SetRenderer()
{
	s_pSDLRenderer = SDL_CreateRenderer(s_pSDLWindow, -1, SDL_RENDERER_ACCELERATED);
}


void SDL::SetWindow()
{
	s_pSDLWindow = SDL_CreateWindow("PlatEngine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_windowWidth, m_windowHeight, SDL_WINDOW_SHOWN); // TODO: Find a magical place for these magic numbers...
}

void SDL::OpenWindow(int windowWidth, int windowHeight)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
	{
		SDL_Log("Window failed to SDL_Init!\n");
		return;
	}

	if (s_pSDLWindow == nullptr)
	{
		m_windowWidth = windowWidth;
		m_windowHeight = windowHeight;
		SDL::SetWindow();
		SDL::SetRenderer();
	}
};

void SDL::CloseWindow() 
{
	SDL_Quit();
};

bool SDL::RunPollEvent()
{

	SDL_Event event;
	SDL_PumpEvents();

	while (SDL_PollEvent(&event))
	{
		// quit?
		if (event.type == SDL_QUIT)
		{
			return false;
		}

		// key down?
		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				Input::DeleteInput();
				return false;
			}
			Input::GetInput()->ExecuteKey(SDL_GetKeyName(event.key.keysym.sym));
		}
	}

	return true; // the user hasn't chosen to end the program
};

void SDL::Render(RenderQueue& queue, const Camera* pCamera)
{
	m_oldTime = m_currentTime;
	m_currentTime = SDL_GetTicks();
	g_deltaTime = (m_currentTime - m_oldTime);

	// Setting the renderer
	SDL_SetRenderDrawColor(s_pSDLRenderer, 0, 0, 0, 255);
	SDL_RenderClear(s_pSDLRenderer);

	// TODO: Convert to a priority queue!
	// going through the render queue and rendering each tile.
	const std::vector<RenderComponent*> tilesToRender = queue.GetTiles();
	for (unsigned int i = 0; i < tilesToRender.size(); ++i)
	{
		// Apply camera offset to tile positions
		int cameraX = pCamera->GetRect()->x;
		int cameraY = pCamera->GetRect()->y;
		float x = tilesToRender[i]->m_x - cameraX;
		float y = tilesToRender[i]->m_y - cameraY;
		float w = tilesToRender[i]->m_w;
		float h = tilesToRender[i]->m_h;

		// If its out of camera bounds than bail
		if (x > k_windowWidth || y > k_windowHeight || x < 0 - w || y < 0 - h)
			continue;

		float tX = tilesToRender[i]->m_textureX;
		float tY = tilesToRender[i]->m_textureY;

		tilesToRender[i]->GetSprite()->DrawSprite(x, y, w, h, tX, tY);
	}
	
	// Now that the background is drawn, draw the gameObjects over it
	const std::vector<GameObject*> gameObjectsToRender = queue.GetGameObjects();
	for (auto it : gameObjectsToRender)
	{
		// TODO: Remove these cast's!
		RenderComponent* pRender = dynamic_cast<RenderComponent*>(it->GetComponent(ComponentType::k_RendererComponent));
		TransformComponent* pTransform = dynamic_cast<TransformComponent*>(it->GetComponent(ComponentType::k_TransformComponent));
		float x = pTransform->GetX();
		float y = pTransform->GetY();
		if (pCamera || strcmp( it->GetName(), "Player" ))
		{
			x -= pCamera->GetRect()->x;
			y -= pCamera->GetRect()->y;
		}

		pRender->GetSprite()->DrawSprite(x, y, pTransform->GetWidth(), pTransform->GetHeight(), 0, 0);
	}
	SDL_Delay(1);
	SDL_RenderPresent(s_pSDLRenderer);
}
