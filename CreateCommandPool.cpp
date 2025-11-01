#include "CreateCommandPool.hpp"

void CreateCommandPool::gCreateCommandPool()
{
	createCommandPool();
	gVulkanContext.commandPool = commandPool;
}

void CreateCommandPool::cleanUp()
{
	vkDestroyCommandPool(gVulkanContext.device, commandPool, nullptr);
	gVulkanContext.commandPool = nullptr;
}

void CreateCommandPool::createCommandPool()
{
	QueueFamilyIndices queueFamilyIndices = QueueFamilyIndices::findQueueFamilies(gVulkanContext.physicalDevice);

	VkCommandPoolCreateInfo poolInfo{};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

	if (vkCreateCommandPool(gVulkanContext.device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS)
	{
		throw std::runtime_error("!-- Failed to create command pool --!");
	}
}