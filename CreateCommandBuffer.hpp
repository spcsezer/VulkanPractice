#pragma once

#include"GlobalState.hpp"

class CreateCommandBuffer
{
private:

	std::vector<VkCommandBuffer> commandBuffers;

	void createCommandBuffers();

public:

	void gCreateCommandBuffer();

	static VkCommandBuffer beginSingleTimeCommands();
	static void endSingleTimeCommands(VkCommandBuffer commandBuffer);

	static void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
};