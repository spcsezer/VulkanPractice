#include "CreateSyncObjects.hpp"

void CreateSyncObjects::gCreateSyncObjects()
{
	createSyncObjects();
	gVulkanContext.imageAvailableSemaphores = imageAvailableSemaphores;
	gVulkanContext.renderFinishedSemaphores = renderFinishedSemaphores;
	gVulkanContext.inFlightFences = inFlightFences;
}

void CreateSyncObjects::cleanUp()
{
	for (size_t i = 0; i < gVulkanContext.MAX_FRAMES_IN_FLIGHT; i++)
	{
		vkDestroySemaphore(gVulkanContext.device, imageAvailableSemaphores[i], nullptr);
		vkDestroySemaphore(gVulkanContext.device, renderFinishedSemaphores[i], nullptr);
		vkDestroyFence(gVulkanContext.device, inFlightFences[i], nullptr);
	}
}

void CreateSyncObjects::createSyncObjects()
{
	imageAvailableSemaphores.resize(gVulkanContext.MAX_FRAMES_IN_FLIGHT);
	renderFinishedSemaphores.resize(gVulkanContext.MAX_FRAMES_IN_FLIGHT);
	inFlightFences.resize(gVulkanContext.MAX_FRAMES_IN_FLIGHT);

	VkSemaphoreCreateInfo semaphoreInfo{};
	semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	VkFenceCreateInfo fenceInfo{};
	fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	for (size_t i = 0; i < gVulkanContext.MAX_FRAMES_IN_FLIGHT; i++)
	{
		if (vkCreateSemaphore(gVulkanContext.device, &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) != VK_SUCCESS ||
			vkCreateSemaphore(gVulkanContext.device, &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) != VK_SUCCESS ||
			vkCreateFence(gVulkanContext.device, &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS)
		{
			throw std::runtime_error("!-- Failed to create synchronization objects for a frame --!");
		}
	}
}