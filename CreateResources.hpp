#pragma once

#include"GlobalState.hpp"
#include"CreateImageViews.hpp"
#include"CreateCommandBuffer.hpp"

class CreateResources
{
private:

	VkImage colorImage;
	VkDeviceMemory colorImageMemory;
	VkImageView colorImageView;

	VkImage depthImage;
	VkDeviceMemory depthImageMemory;
	VkImageView depthImageView;

	void createColorResources();
	void createDepthResources();

	VkFormat findDepthFormat();

	VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

	static bool hasStencilComponent(VkFormat format);

public:

	void gCreateResources();
	void cleanUp();

	static void createImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkSampleCountFlagBits numSamples, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);

	static uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

	static void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels);
};