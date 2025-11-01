#include "CreateLogicalDevice.hpp"

void CreateLogicalDevice::gCreateLogicalDevice()
{
	createLogicalDevice();
	gVulkanContext.device = device;
}

void CreateLogicalDevice::cleanUp()
{
	vkDestroyDevice(device, nullptr);
	gVulkanContext.device = nullptr;
}

void CreateLogicalDevice::createLogicalDevice()
{
	QueueFamilyIndices indices = QueueFamilyIndices::findQueueFamilies(gVulkanContext.physicalDevice);

	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };

	float queuePriority = 1.0f;
	for (uint32_t queueFamily : uniqueQueueFamilies)
	{
		VkDeviceQueueCreateInfo queueCreateInfo{};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueFamily;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;
		queueCreateInfos.push_back(queueCreateInfo);
	}

	VkPhysicalDeviceFeatures deviceFeatures{};
	deviceFeatures.samplerAnisotropy = VK_TRUE;

	VkDeviceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
	createInfo.pQueueCreateInfos = queueCreateInfos.data();
	createInfo.pEnabledFeatures = &deviceFeatures;
	createInfo.enabledExtensionCount = static_cast<uint32_t>(gVulkanContext.deviceExtensions.size());
	createInfo.ppEnabledExtensionNames = gVulkanContext.deviceExtensions.data();

	if (gVulkanContext.validationLayers->getEnableValidationLayers())
	{
		createInfo.enabledLayerCount = static_cast<uint32_t>(gVulkanContext.validationLayers->getValidationLayers().size());
		createInfo.ppEnabledLayerNames = gVulkanContext.validationLayers->getValidationLayers().data();
	}
	else
	{
		createInfo.enabledLayerCount = 0;
	}

	if (vkCreateDevice(gVulkanContext.physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS)
	{
		throw std::runtime_error("!-- Failed to create logical device --!");
	}
	vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &gVulkanContext.graphicsQueue);
	vkGetDeviceQueue(device, indices.presentFamily.value(), 0, &gVulkanContext.presentQueue);
}