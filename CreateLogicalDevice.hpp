#pragma once

#include"GlobalState.hpp"
#include"QueueFamilies.hpp"
#include"ValidationLayers.hpp"

class CreateLogicalDevice
{
private:

	VkDevice device;

	void createLogicalDevice();

public:

	void gCreateLogicalDevice();
	void cleanUp();
};