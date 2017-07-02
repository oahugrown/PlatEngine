// EventPoll.h

#ifndef EVENTPOLL_H
#define EVENTPOLL_H

#include "../Graphics/GraphicsFactory.h"

// TODO: Decouple this from the graphics side of things...
class EventPoll
{
private:
	GraphicsFactory* m_pGraphics;

public:
	EventPoll(GraphicsFactory* pGraphicsType)
		: m_pGraphics(pGraphicsType)
	{
		//
	}
	bool RunEventPoll()
	{
		if (m_pGraphics->GetGraphics())
		{
			return m_pGraphics->GetGraphics()->RunPollEvent();
		}
		return false;
	};
};


#endif // !EVENTPOLL_H


