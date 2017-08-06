// Sprite.h

#ifndef SPRITE_H
#define SPRITE_H

class Sprite
{
private:
	float u, v, u2, v2;

public:
	Sprite() {};
	virtual ~Sprite(){};

	// The following return true upon successful execution
	virtual bool DrawSprite(float u, float v, float u2, float v2, float tX, float tY) = 0;
	virtual bool LoadImage() = 0;
	virtual void SetFile(const char* pFile) = 0;
};


#endif //!SPRITE_H