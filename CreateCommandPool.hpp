#pragma once

#include"GlobalState.hpp"
#include"QueueFamilies.hpp"

class CreateCommandPool
{
private:

	VkCommandPool commandPool;

	void createCommandPool();

public:

	void gCreateCommandPool();
	void cleanUp();
};