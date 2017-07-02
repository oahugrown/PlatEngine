#ifndef RENDERMANAGERINTERFACE_H
#define RENDERMANAGERINTERFACE_H

class GraphicsFactory;
class Camera;

class RenderManagerInterface
{
protected:
	GraphicsFactory* m_pGraphics;
public:
	RenderManagerInterface() {};
	virtual ~RenderManagerInterface() {};
	// To be implemented by the child class to determine which rendering
	// system to start up.
	virtual void StartUp() = 0;
	// To be implemented by the child class to determine which rendering
	// system to shut down.
	virtual void ShutDown() = 0;
	// Whatever system is used, get it and render the sprites in the world.
	virtual void DrawSprites(const Camera* camera) = 0;

	GraphicsFactory* GetGraphicsFactory() const { return m_pGraphics; };
};

#endif // RENDERMANAGER_INTERFACE_H