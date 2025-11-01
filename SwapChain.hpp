#pragma once

#include"GlobalState.hpp"
#include"SwapChainSupportDetails.hpp"
#include"QueueFamilies.hpp"
#include"CreateImageViews.hpp"
#include"CreateResources.hpp"
#include"CreateFrameBuffers.hpp"

class SwapChain
{
private:

	VkSwapchainKHR swapchain;

	std::vector<VkImage> swapchainImages;
	VkFormat swapchainImageFormat;
	VkExtent2D swapchainExtent;

	void createSwapChain();

	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

public:

	void gSwapChain();
	void cleanUp();

	static void cleanupSwapChain();
	static void reCreateSwapChain();
};