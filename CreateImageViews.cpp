#include "CreateImageViews.hpp"

void CreateImageViews::gCreateImageViews()
{
	createImageViews();
	gVulkanContext.swapchainImageViews = swapchainImageViews;
}

void CreateImageViews::cleanUp()
{
	for (auto imageView : swapchainImageViews)
	{
		vkDestroyImageView(gVulkanContext.device, imageView, nullptr);
	}
}

void CreateImageViews::createImageViews()
{
	swapchainImageViews.resize(gVulkanContext.swapchainImages.size());

	for (size_t i = 0; i < gVulkanContext.swapchainImages.size(); i++)
	{
		swapchainImageViews[i] = createImageView(gVulkanContext.swapchainImages[i], gVulkanContext.swapchainImageFormat, VK_IMAGE_ASPECT_COLOR_BIT, 1);
	}
}

VkImageView CreateImageViews::createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels)
{
	VkImageViewCreateInfo viewInfo{};
	viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	viewInfo.image = image;
	viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	viewInfo.format = format;
	viewInfo.subresourceRange.aspectMask = aspectFlags;
	viewInfo.subresourceRange.baseMipLevel = 0;
	viewInfo.subresourceRange.levelCount = mipLevels;
	viewInfo.subresourceRange.baseArrayLayer = 0;
	viewInfo.subresourceRange.layerCount = 1;

	VkImageView imageView;

	if (vkCreateImageView(gVulkanContext.device, &viewInfo, nullptr, &imageView) != VK_SUCCESS)
	{
		throw std::runtime_error("!-- Failed to create texture image view --!");
	}
	return imageView;
}