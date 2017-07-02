// TransformComponent.h

#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "Component.h"

class TransformComponent: public Component
{
private:
	float m_positionX, m_positionY, m_width, m_height;
public:
	// TODO: Apply Scale!
	TransformComponent(float x, float y) 
	{
		m_positionX = x;
		m_positionY = y;
	};
	~TransformComponent() {};

	// Getters
	float GetX() const { return m_positionX; };
	float GetY() const { return m_positionY; };
	float GetWidth() const { return m_width; };
	float GetHeight() const { return m_height; };

	// Setters
	void SetX(float newX) { m_positionX = newX; };
	void SetY(float newY) { m_positionY = newY; };
	void SetWidth(float newWidth) { m_width = newWidth; };
	void SetHeight(float newHeight) { m_height = newHeight; };
};

#endif // !TRANSFORMCOMPONENT_H