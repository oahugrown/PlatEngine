// InputHandler.h

#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#ifdef PLATENGINE_EXPORTS
#define INPUTHANDLER_API __declspec(dllimport) 
#else
#define INPUTHANDLER_API __declspec(dllexport) 
#endif

#include <functional>
#include "Input.h"
#include <unordered_map>
#include <vector>

class InputHandler
{
	std::unordered_map<std::string, std::vector<std::function<void()>>> m_functions;

public:
	INPUTHANDLER_API InputHandler():m_functions(NULL){};
	INPUTHANDLER_API ~InputHandler() {};
	bool INPUTHANDLER_API BindKey(const std::string& key, std::function<void()> functionToExecute);
	bool INPUTHANDLER_API RemoveKeyBind(const std::string& key, std::function<void()> functionToRemove);
	void INPUTHANDLER_API Execute(const std::string& key);

};

#endif // !INPUTHANDLER_H
