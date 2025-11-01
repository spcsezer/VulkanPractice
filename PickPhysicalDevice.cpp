#include "PickPhysicalDevice.hpp"

void PickPhysicalDevice::gPickPhysicalDevice()
{
	pickPhysicalDevice();
	gVulkanContext.physicalDevice = physicalDevice;
	gVulkanContext.msaaSamples = msaaSamples;
}

void PickPhysicalDevice::pickPhysicalDevice()
{
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(gVulkanContext.instance, &deviceCount, nullptr);
	if (deviceCount == 0)
	{
		throw std::runtime_error("!-- Vulkan didn't found any compatible graphic card --!");
	}
	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(gVulkanContext.instance, &deviceCount, devices.data());

	std::multimap<int, VkPhysicalDevice> candidates;

	for (const auto& device : devices)
	{
		int score = rateDeviceSuitability(device);
		candidates.insert(std::make_pair(score, device));
	}

	if (candidates.rbegin()->first > 0)
	{
		physicalDevice = candidates.rbegin()->second;
		msaaSamples = getMaxUsableSampleCount();
	}
	else
	{
		throw std::runtime_error("!-- Failed to find suitable GPU --!");
	}
}

int PickPhysicalDevice::rateDeviceSuitability(VkPhysicalDevice device)
{
	VkPhysicalDeviceProperties deviceProperties;
	VkPhysicalDeviceFeatures deviceFeatures;

	vkGetPhysicalDeviceProperties(device, &deviceProperties);
	vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

	int score = 0;

	if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
	{
		score += 1000;
	}

	score += deviceProperties.limits.maxImageDimension2D;

	if (!deviceFeatures.geometryShader)
	{
		return 0;
	}
	return score;
}

VkSampleCountFlagBits PickPhysicalDevice::getMaxUsableSampleCount()
{
	VkPhysicalDeviceProperties physicalDeviceProperties{};
	vkGetPhysicalDeviceProperties(physicalDevice, &physicalDeviceProperties);

	VkSampleCountFlags counts = physicalDeviceProperties.limits.framebufferColorSampleCounts & physicalDeviceProperties.limits.framebufferDepthSampleCounts;

	if (counts & VK_SAMPLE_COUNT_64_BIT)
	{
		return VK_SAMPLE_COUNT_64_BIT;
	}
	if (counts & VK_SAMPLE_COUNT_32_BIT)
	{
		return VK_SAMPLE_COUNT_32_BIT;
	}
	if (counts & VK_SAMPLE_COUNT_16_BIT)
	{
		return VK_SAMPLE_COUNT_16_BIT;
	}
	if (counts & VK_SAMPLE_COUNT_8_BIT)
	{
		return VK_SAMPLE_COUNT_8_BIT;
	}
	if (counts & VK_SAMPLE_COUNT_4_BIT)
	{
		return VK_SAMPLE_COUNT_4_BIT;
	}
	if (counts & VK_SAMPLE_COUNT_2_BIT)
	{
		return VK_SAMPLE_COUNT_2_BIT;
	}
	return VK_SAMPLE_COUNT_1_BIT;
}