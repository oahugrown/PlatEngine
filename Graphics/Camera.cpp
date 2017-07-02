#include "Camera.h"

#include "Macros.h"

Camera::Camera(int screenWidth, int screenHeight, int levelWidth, int levelHeight)
	: m_camLockedInWorld(false)
	, m_levelHeight(levelHeight)
	, m_levelWidth(levelWidth)
	, m_screenHeight(screenHeight)
	, m_screenWidth(screenWidth)
{
	m_pPosition = new Rect();
}

Camera::~Camera()
{
	SAFE_DELETE(m_pPosition);
}

void Camera::SetPosition(int xFocusPoint, int yFocusPoint, int offsetX, int offsetY)
{
	m_pPosition->x = (xFocusPoint - offsetX) - m_screenWidth / 2;
	m_pPosition->y = (yFocusPoint - offsetY) - m_screenHeight / 2;

	// If the camera is set to not travel out of the world
	// Then lock its position in the world
	if (m_camLockedInWorld)
	{
		if (m_pPosition->x < 0)
			m_pPosition->x = 0;
		else if (m_pPosition->x > (m_levelWidth - m_screenWidth))
			m_pPosition->x = m_levelWidth - m_screenWidth;
		
		if (m_pPosition->y < 0)
			m_pPosition->y = 0;
		else if (m_pPosition->y > (m_levelHeight - m_screenHeight))
			m_pPosition->y = m_levelHeight - m_screenHeight;
	}

}
