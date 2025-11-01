#pragma once

#include"GlobalState.hpp"

class CreateSurface
{
private:

	VkSurfaceKHR surface;

	void createSurface();

public:

	void gCreateSurface();
	void cleanUp();
};

