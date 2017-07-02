// GraphicsRenderer.h

#ifndef GRAPHICSRENDERER_H
#define GRAPHICSRENDERER_H

class RenderQueue;
class Camera;

struct SpecialDrawRect
{
	int textureX = 0;
	int textureY = 0;
	int screenX = 0;
	int screenY = 0;
};

class GraphicsRenderer
{
private:

public:
	virtual void OpenWindow(int windowWidth, int windowHeight) = 0;
	virtual void CloseWindow() = 0;
	virtual bool RunPollEvent() = 0;
	virtual void Render(RenderQueue& queue, const Camera* pCamera) = 0;
};


#endif //!GRAPHICSFACTORY_H