#pragma once

#include"GlobalState.hpp"

class CreateImageViews
{
private:

	std::vector<VkImageView> swapchainImageViews;

	void createImageViews();

public:

	void gCreateImageViews();
	void cleanUp();

	static VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);
};