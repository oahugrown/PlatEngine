// GraphicsFactory.h

#ifndef GRAPHICSFACTORY_H
#define GRAPHICSFACTORY_H

#include "..\Graphics\GraphicsRenderer.h"

class GraphicsFactory
{
private:
	GraphicsRenderer* m_pGraphicsRender;
	GraphicsRenderer* GetSDL();

public:
	GraphicsFactory();
	~GraphicsFactory();
	GraphicsRenderer* GetGraphics();
};

#endif	// !GRAPHICSFACTORY_H