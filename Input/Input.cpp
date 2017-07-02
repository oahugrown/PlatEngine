#include "Input.h"
#include "InputHandler.h"
#include "Macros.h"


Input* Input::s_instance = nullptr;

Input* Input::GetInput() 
{
	if (s_instance == nullptr)
		s_instance = new Input();

	return s_instance;
};


void Input::ExecuteKey(const std::string& key)
{
    auto findIt = s_processedInputs.find(key);
    if (findIt != s_processedInputs.end())
    {
        std::vector<InputHandler*>& handlers = findIt->second;
        for (InputHandler* pHandler : handlers)
        {
            pHandler->Execute(key);
        }
    }
}
bool Input::RegisterHandler(const std::string& key, InputHandler* pHandler)
{
	// Verify our listener isn't nullptr
	if (!pHandler)
		return false;

	// Add it
	s_processedInputs[key].push_back(pHandler);
	return true;
}

bool Input::UnregisterHandler(const std::string& key, InputHandler* pHandler)
{
	// Check all the elements remove the correct listener
	for (unsigned int i = 0; i < s_processedInputs[key].size(); ++i)
	{
		if (s_processedInputs[key][i] == pHandler)
		{
			s_processedInputs[key].erase(s_processedInputs[key].begin() + i);
			return true;
		}
	}


	return false;
}

