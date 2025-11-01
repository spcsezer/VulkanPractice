#pragma once

#include"GlobalState.hpp"

class PickPhysicalDevice
{
private:

	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkSampleCountFlagBits msaaSamples = VK_SAMPLE_COUNT_1_BIT;

	void pickPhysicalDevice();

	int rateDeviceSuitability(VkPhysicalDevice device);

	VkSampleCountFlagBits getMaxUsableSampleCount();

public:

	void gPickPhysicalDevice();
};