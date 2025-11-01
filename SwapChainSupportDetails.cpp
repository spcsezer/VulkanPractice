#include "SwapChainSupportDetails.hpp"

SwapChainSupportDetails SwapChainSupportDetails::querySwapChainSupport(VkPhysicalDevice device)
{
	SwapChainSupportDetails details;

	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, gVulkanContext.surface, &details.capabilities);

	uint32_t formatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(device, gVulkanContext.surface, &formatCount, nullptr);
	if (formatCount != 0)
	{
		details.formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, gVulkanContext.surface, &formatCount, details.formats.data());
	}

	uint32_t presentModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(device, gVulkanContext.surface, &presentModeCount, nullptr);
	if (presentModeCount != 0)
	{
		details.presentMode.resize(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, gVulkanContext.surface, &presentModeCount, details.presentMode.data());
	}

	return details;
}