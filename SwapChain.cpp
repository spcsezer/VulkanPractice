#include "SwapChain.hpp"

void SwapChain::gSwapChain()
{
	createSwapChain();
	gVulkanContext.swapchain = swapchain;
	gVulkanContext.swapchainImages = swapchainImages;
	gVulkanContext.swapchainExtent = swapchainExtent;
	gVulkanContext.swapchainImageFormat = swapchainImageFormat;
}

void SwapChain::cleanUp()
{
	vkDestroySwapchainKHR(gVulkanContext.device, swapchain, nullptr);
	gVulkanContext.swapchain = VK_NULL_HANDLE;
}

void SwapChain::createSwapChain()
{
	SwapChainSupportDetails swapChainSupport = SwapChainSupportDetails::querySwapChainSupport(gVulkanContext.physicalDevice);

	VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
	VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentMode);
	VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);

	uint32_t imageCount = swapChainSupport.capabilities.minImageCount;

	if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount)
	{
		imageCount = swapChainSupport.capabilities.maxImageCount;
	}

	VkSwapchainCreateInfoKHR createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.surface = gVulkanContext.surface;
	createInfo.minImageCount = imageCount;
	createInfo.imageFormat = surfaceFormat.format;
	createInfo.imageColorSpace = surfaceFormat.colorSpace;
	createInfo.imageExtent = extent;
	createInfo.imageArrayLayers = 1;
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	QueueFamilyIndices indices = QueueFamilyIndices::findQueueFamilies(gVulkanContext.physicalDevice);
	uint32_t queueFamilyIndices[] = { indices.graphicsFamily.value(), indices.presentFamily.value() };

	if (indices.graphicsFamily != indices.presentFamily)
	{
		createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		createInfo.queueFamilyIndexCount = 2;
		createInfo.pQueueFamilyIndices = queueFamilyIndices;
	}
	else
	{
		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		createInfo.queueFamilyIndexCount = 0;
		createInfo.pQueueFamilyIndices = nullptr;
	}
	createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	createInfo.presentMode = presentMode;
	createInfo.clipped = VK_TRUE;
	createInfo.oldSwapchain = VK_NULL_HANDLE;

	if (vkCreateSwapchainKHR(gVulkanContext.device, &createInfo, nullptr, &swapchain) != VK_SUCCESS)
	{
		throw std::runtime_error("!-- Failed to create swapchain --!");
	}

	vkGetSwapchainImagesKHR(gVulkanContext.device, swapchain, &imageCount, nullptr);
	swapchainImages.resize(imageCount);
	vkGetSwapchainImagesKHR(gVulkanContext.device, swapchain, &imageCount, swapchainImages.data());

	swapchainImageFormat = surfaceFormat.format;
	swapchainExtent = extent;
}

void SwapChain::cleanupSwapChain()
{
	vkDestroyImageView(gVulkanContext.device, gVulkanContext.colorImageView, nullptr);
	vkDestroyImage(gVulkanContext.device, gVulkanContext.colorImage, nullptr);
	vkFreeMemory(gVulkanContext.device, gVulkanContext.colorImageMemory, nullptr);

	vkDestroyImageView(gVulkanContext.device, gVulkanContext.depthImageView, nullptr);
	vkDestroyImage(gVulkanContext.device, gVulkanContext.depthImage, nullptr);
	vkFreeMemory(gVulkanContext.device, gVulkanContext.depthImageMemory, nullptr);

	for (auto framebuffer : gVulkanContext.swapchainFrameBuffers)
	{
		vkDestroyFramebuffer(gVulkanContext.device, framebuffer, nullptr);
	}

	for (auto imageView : gVulkanContext.swapchainImageViews)
	{
		vkDestroyImageView(gVulkanContext.device, imageView, nullptr);
	}

	vkDestroySwapchainKHR(gVulkanContext.device, gVulkanContext.swapchain, nullptr);
}

void SwapChain::reCreateSwapChain()
{
	int width = 0, height = 0;
	glfwGetFramebufferSize(gVulkanContext.window, &width, &height);
	while (width == 0 || height == 0)
	{
		glfwGetFramebufferSize(gVulkanContext.window, &width, &height);
		glfwWaitEvents();
	}

	vkDeviceWaitIdle(gVulkanContext.device);

	cleanupSwapChain();

	//createSwapChain();
	SwapChain swapChain;
	swapChain.createSwapChain();
	//createImageViews();
	CreateImageViews createImageViews;
	createImageViews.gCreateImageViews();
	//createColorResources();
	//createDepthResources();
	CreateResources createResources;
	createResources.gCreateResources();
	//createFrameBuffers();
	CreateFrameBuffers createFrameBuffers;
	createFrameBuffers.gCreateFrameBuffers();
}

VkSurfaceFormatKHR SwapChain::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
{
	for (const auto& availableFormat : availableFormats)
	{
		if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLORSPACE_SRGB_NONLINEAR_KHR)
		{
			return availableFormat;
		}
	}
	return availableFormats[0];
}

VkPresentModeKHR SwapChain::chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
{
	for (const auto& availablePresentMode : availablePresentModes)
	{
		if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
		{
			return availablePresentMode;
		}
	}
	return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D SwapChain::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
{
	if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
	{
		return capabilities.currentExtent;
	}
	else
	{
		int width, height;
		glfwGetFramebufferSize(gVulkanContext.window, &width, &height);

		VkExtent2D actualExtent = {
			static_cast<uint32_t>(width),
			static_cast<uint32_t>(height)
		};

		actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
		actualExtent.height = std::clamp(actualExtent.width, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

		return actualExtent;
	}
}