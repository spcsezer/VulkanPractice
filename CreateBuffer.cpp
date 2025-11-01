#include "CreateBuffer.hpp"

void CreateBuffer::gCreateBuffer()
{
	createVertexBuffer();
	createIndexBuffer();
	createUniformBuffers();

	gVulkanContext.vertexBuffer = vertexBuffer;
	gVulkanContext.indexBuffer = indexBuffer;
	gVulkanContext.uniformBuffers = uniformBuffers;
	gVulkanContext.uniformBuffersMapped = uniformBuffersMapped;
}

void CreateBuffer::cleanUp()
{
	for (size_t i = 0; i < gVulkanContext.MAX_FRAMES_IN_FLIGHT; i++)
	{
		vkDestroyBuffer(gVulkanContext.device, uniformBuffers[i], nullptr);
		vkFreeMemory(gVulkanContext.device, uniformBuffersMemory[i], nullptr);
	}
	vkDestroyBuffer(gVulkanContext.device, vertexBuffer, nullptr);
	vkFreeMemory(gVulkanContext.device, vertexBufferMemory, nullptr);
	vkDestroyBuffer(gVulkanContext.device, indexBuffer, nullptr);
	vkFreeMemory(gVulkanContext.device, indexBufferMemory, nullptr);
}

void CreateBuffer::createVertexBuffer()
{
	VkDeviceSize bufferSize = sizeof(gVulkanContext.vertices[0]) * gVulkanContext.vertices.size();

	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;

	createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

	void* data;
	vkMapMemory(gVulkanContext.device, stagingBufferMemory, 0, bufferSize, 0, &data);
	memcpy(data, gVulkanContext.vertices.data(), (size_t)bufferSize);
	vkUnmapMemory(gVulkanContext.device, stagingBufferMemory);

	createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer, vertexBufferMemory);

	copyBuffer(stagingBuffer, vertexBuffer, bufferSize);

	vkDestroyBuffer(gVulkanContext.device, stagingBuffer, nullptr);
	vkFreeMemory(gVulkanContext.device, stagingBufferMemory, nullptr);
}

void CreateBuffer::createIndexBuffer()
{
	VkDeviceSize bufferSize = sizeof(gVulkanContext.indices[0]) * gVulkanContext.indices.size();

	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;
	createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

	void* data;
	vkMapMemory(gVulkanContext.device, stagingBufferMemory, 0, bufferSize, 0, &data);
	memcpy(data, gVulkanContext.indices.data(), (size_t)bufferSize);
	vkUnmapMemory(gVulkanContext.device, stagingBufferMemory);

	createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, indexBufferMemory);

	copyBuffer(stagingBuffer, indexBuffer, bufferSize);

	vkDestroyBuffer(gVulkanContext.device, stagingBuffer, nullptr);
	vkFreeMemory(gVulkanContext.device, stagingBufferMemory, nullptr);
}

void CreateBuffer::createUniformBuffers()
{
	VkDeviceSize bufferSize = sizeof(UniformBufferObject);

	uniformBuffers.resize(gVulkanContext.MAX_FRAMES_IN_FLIGHT);
	uniformBuffersMemory.resize(gVulkanContext.MAX_FRAMES_IN_FLIGHT);
	uniformBuffersMapped.resize(gVulkanContext.MAX_FRAMES_IN_FLIGHT);

	for (size_t i = 0; i < gVulkanContext.MAX_FRAMES_IN_FLIGHT; i++)
	{
		createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffers[i], uniformBuffersMemory[i]);

		vkMapMemory(gVulkanContext.device, uniformBuffersMemory[i], 0, bufferSize, 0, &uniformBuffersMapped[i]);
	}
}

void CreateBuffer::copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size)
{
	VkCommandBuffer commandBuffer = CreateCommandBuffer::beginSingleTimeCommands();

	VkBufferCopy copyRegion{};
	copyRegion.size = size;
	vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

	CreateCommandBuffer::endSingleTimeCommands(commandBuffer);
}

void CreateBuffer::copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height)
{
	VkCommandBuffer commandBuffer = CreateCommandBuffer::beginSingleTimeCommands();

	VkBufferImageCopy region{};
	region.bufferOffset = 0;
	region.bufferRowLength = 0;
	region.bufferImageHeight = 0;
	region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	region.imageSubresource.mipLevel = 0;
	region.imageSubresource.baseArrayLayer = 0;
	region.imageSubresource.layerCount = 1;
	region.imageOffset = { 0, 0, 0 };
	region.imageExtent = { width, height, 1 };

	vkCmdCopyBufferToImage(commandBuffer, buffer, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

	CreateCommandBuffer::endSingleTimeCommands(commandBuffer);
}

void CreateBuffer::createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory)
{
	VkBufferCreateInfo bufferInfo{};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.size = size;
	bufferInfo.usage = usage;
	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	if (vkCreateBuffer(gVulkanContext.device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS)
	{
		throw std::runtime_error("!-- Failed to create buffer --!");
	}

	VkMemoryRequirements memRequirements;
	vkGetBufferMemoryRequirements(gVulkanContext.device, buffer, &memRequirements);

	VkMemoryAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = CreateResources::findMemoryType(memRequirements.memoryTypeBits, properties);

	if (vkAllocateMemory(gVulkanContext.device, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS)
	{
		throw std::runtime_error("!-- Failed to allocate buffer memory --!");
	}

	vkBindBufferMemory(gVulkanContext.device, buffer, bufferMemory, 0);
}

void CreateBuffer::updateUniformBuffer(uint32_t currentImage)
{
	//static auto startTime = std::chrono::high_resolution_clock::now();
	//auto currentTime = std::chrono::high_resolution_clock::now();

	//float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
	//ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	UniformBufferObject ubo{};
	//ubo.model = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, -1.0f, 1.0f));
	ubo.model = glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	//ubo.model = glm::mat4(1.0f);
	ubo.view = glm::lookAt(gVulkanContext.camera.position, gVulkanContext.camera.position + gVulkanContext.camera.front, glm::vec3(0.0f, 1.0f, 0.0f));
	ubo.proj = glm::perspective(glm::radians(45.0f), gVulkanContext.swapchainExtent.width / (float)gVulkanContext.swapchainExtent.height, 0.1f, 10.0f);
	ubo.proj[1][1] *= -1;
	memcpy(gVulkanContext.uniformBuffersMapped[currentImage], &ubo, sizeof(ubo));
}