#pragma once

#include"GlobalState.hpp"
#include"SwapChain.hpp"
#include"CreateCommandBuffer.hpp"
#include"CreateBuffer.hpp"

void drawFrame()
{
	vkWaitForFences(gVulkanContext.device, 1, &gVulkanContext.inFlightFences[gVulkanContext.currentFrame], VK_TRUE, UINT64_MAX);

	uint32_t imageIndex;
	VkResult result = vkAcquireNextImageKHR(gVulkanContext.device, gVulkanContext.swapchain, UINT64_MAX, gVulkanContext.imageAvailableSemaphores[gVulkanContext.currentFrame], VK_NULL_HANDLE, &imageIndex);

	if (result == VK_ERROR_OUT_OF_DATE_KHR)
	{
		SwapChain::reCreateSwapChain();
		return;
	}
	else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
	{
		throw std::runtime_error("!-- Failed to acquire swapchain image --!");
	}
	vkResetFences(gVulkanContext.device, 1, &gVulkanContext.inFlightFences[gVulkanContext.currentFrame]);

	vkResetCommandBuffer(gVulkanContext.commandBuffers[gVulkanContext.currentFrame], 0);
	CreateCommandBuffer::recordCommandBuffer(gVulkanContext.commandBuffers[gVulkanContext.currentFrame], imageIndex);

	CreateBuffer::updateUniformBuffer(gVulkanContext.currentFrame);

	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	VkSemaphore waitSemaphores[] = { gVulkanContext.imageAvailableSemaphores[gVulkanContext.currentFrame] };
	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };

	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &gVulkanContext.commandBuffers[gVulkanContext.currentFrame];

	VkSemaphore signalSemaphores[] = { gVulkanContext.renderFinishedSemaphores[gVulkanContext.currentFrame] };

	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;

	if (vkQueueSubmit(gVulkanContext.graphicsQueue, 1, &submitInfo, gVulkanContext.inFlightFences[gVulkanContext.currentFrame]) != VK_SUCCESS)
	{
		throw std::runtime_error("!-- Failed to submit draw command buffer --!");
	}

	VkPresentInfoKHR presentInfo{};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = signalSemaphores;

	VkSwapchainKHR swapchains[] = { gVulkanContext.swapchain };

	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapchains;
	presentInfo.pImageIndices = &imageIndex;
	presentInfo.pResults = nullptr;

	result = vkQueuePresentKHR(gVulkanContext.presentQueue, &presentInfo);
	if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || gVulkanContext.frameBufferResized)
	{
		gVulkanContext.frameBufferResized = false;
		SwapChain::reCreateSwapChain();
	}
	else if (result != VK_SUCCESS)
	{
		throw std::runtime_error("!-- Failed to present swapchain image --!");
	}
	gVulkanContext.currentFrame = (gVulkanContext.currentFrame + 1) % gVulkanContext.MAX_FRAMES_IN_FLIGHT;
}