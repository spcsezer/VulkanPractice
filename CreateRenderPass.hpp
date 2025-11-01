#pragma once

#include"GlobalState.hpp"

class CreateRenderPass
{
private:

	VkRenderPass renderPass;

	void createRenderPass();

	VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
	VkFormat findDepthFormat();

public:

	void gCreateRenderPass();
	void cleanUp();
};