// Input.h

#ifndef INPUT_H
#define INPUT_H

class InputHandler;
#include <vector>
#include <unordered_map>
#include "Macros.h"

// Manages the types of input events
class Input
{
private:
	static Input* s_instance;
	std::unordered_map<std::string, std::vector<InputHandler*>> s_processedInputs;

public:
	static Input* GetInput();
	static void DeleteInput() { SAFE_DELETE(s_instance); };

	// goes through all the Listeners and executes their bound function
	void ExecuteKey(const std::string& key);
	bool RegisterHandler(const std::string& key, InputHandler* pHandler);
	bool UnregisterHandler(const std::string& key, InputHandler* pHandler);
};
 
#endif // !INPUT_H

