#include "InputHandler.h"

bool InputHandler::BindKey(const std::string& key, std::function<void()> function)
{
	// don't bother adding the function if it's null
	if (function == NULL)
		return false;

	std::vector<std::function<void()>> temp;
	temp.push_back(function);
	auto value = std::make_pair(key, temp);
	m_functions.insert(value);
	Input::GetInput()->RegisterHandler(key, this);
	return true;
}

bool InputHandler::RemoveKeyBind(const std::string& key, std::function<void()> functionToRemove)
{
	//if (m_functions.size() == 0)  // not guaranteed O(1), though almost always is
    if (m_functions.empty())  // guaranteed O(1)
		return false;

	for (unsigned int i = 0; i < m_functions.size(); i++)
	{
		if (m_functions[key][i])
		{
			m_functions[key].erase(m_functions[key].begin() + i);
			// if we have no more functions, then remove the listener from our input manager
			if (m_functions.empty())
			{
				Input::GetInput()->UnregisterHandler(key, this);
			}
			return true;
		}
	}
	// couldn't find the function to remove
	return false;
}

void InputHandler::Execute(const std::string& key)
{
	// for each function in our array, call it
	if (m_functions.find(key) != m_functions.end())
	{
		for (auto it : m_functions[key])
		{
			it();
		}
	}
}