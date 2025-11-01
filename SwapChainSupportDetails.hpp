#pragma once

#include"GlobalState.hpp"

struct SwapChainSupportDetails
{
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentMode;

	static SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
};