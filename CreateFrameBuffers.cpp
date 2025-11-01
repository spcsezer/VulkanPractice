#include "CreateFrameBuffers.hpp"

void CreateFrameBuffers::gCreateFrameBuffers()
{
	createFrameBuffers();
	gVulkanContext.swapchainFrameBuffers = swapchainFrameBuffers;
}

void CreateFrameBuffers::cleanUp()
{
	for (auto framebuffer : swapchainFrameBuffers)
	{
		vkDestroyFramebuffer(gVulkanContext.device, framebuffer, nullptr);
	}
}

void CreateFrameBuffers::createFrameBuffers()
{
	swapchainFrameBuffers.resize(gVulkanContext.swapchainImageViews.size());

	for (size_t i = 0; i < gVulkanContext.swapchainImageViews.size(); i++)
	{
		std::array<VkImageView, 3> attachments = { gVulkanContext.colorImageView, gVulkanContext.depthImageView, gVulkanContext.swapchainImageViews[i] };

		VkFramebufferCreateInfo framebufferInfo{};
		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		framebufferInfo.renderPass = gVulkanContext.renderPass;
		framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
		framebufferInfo.pAttachments = attachments.data();
		framebufferInfo.width = gVulkanContext.swapchainExtent.width;
		framebufferInfo.height = gVulkanContext.swapchainExtent.height;
		framebufferInfo.layers = 1;

		if (vkCreateFramebuffer(gVulkanContext.device, &framebufferInfo, nullptr, &swapchainFrameBuffers[i]) != VK_SUCCESS)
		{
			throw std::runtime_error("!-- Failed to create framebuffer --!");
		}
	}
}