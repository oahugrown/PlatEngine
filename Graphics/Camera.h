// Camera.h

#ifndef CAMERA_H
#define CAMERA_H

#include "Rendering/RenderManager.h"

#ifdef PLATENGINE_EXPORTS
#define CAMERA_API __declspec(dllimport) 
#else
#define CAMERA_API __declspec(dllexport) 
#endif

struct Rect
{
	int x, y, w, h;
	Rect() : x(0), y(0), w(0), h(0) {};
};

class Camera
{
private:
	Rect* m_pPosition;
	int m_screenWidth, m_screenHeight,
		m_levelHeight, m_levelWidth;
	bool m_camLockedInWorld;

public:
	CAMERA_API Camera(int screenWidth, int screenHeight, int levelWidth, int levelHeight);
	CAMERA_API ~Camera();
	Rect* GetRect() const { return m_pPosition; };
	void CAMERA_API SetPosition(int xFocusPoint, int yFocusPoint, int offsetX, int offsetY);
	void CAMERA_API LockCameraInWorld() { m_camLockedInWorld = true; };
	void CAMERA_API UnlockCameraInWorld() { m_camLockedInWorld = false; };

};


#endif // !CAMERA_H

