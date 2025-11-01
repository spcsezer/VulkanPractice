#pragma once

#include "GlobalState.hpp"

class CreateInstance
{
private:

	VkInstance instance;

	void createInstance();

	std::vector<const char*> getRequiredExtensions();

public:

	void gCreateInstance();
	void cleanUp();
};

