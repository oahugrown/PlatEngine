// SDLInterface.h

#ifndef SDLINTERFACE_H
#define SDLINTERFACE_H

class SDLInterface
{

public:
	SDLInterface() {};
	virtual ~SDLInterface() {};

	virtual void OpenWindow() = 0;
	virtual void CloseWindow() = 0;
	virtual void RunPollEvent() = 0;

};


#endif // SDLINTERFACE_H