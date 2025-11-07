#include "CreateBuffer.hpp"


void CreateBuffer::gCreateBuffer()
{
	createVertexBuffer(gVulkanContext.vertices, vertexBuffer, vertexBufferMemory);
	createIndexBuffer(gVulkanContext.indices, indexBuffer, indexBufferMemory);
	createUniformBuffers(uniformBuffers, uniformBuffersMemory, uniformBuffersMapped);
	gVulkanContext.vertexBuffer = vertexBuffer;
	gVulkanContext.indexBuffer = indexBuffer;
	gVulkanContext.uniformBuffers = uniformBuffers;
	gVulkanContext.uniformBuffersMapped = uniformBuffersMapped;

	createVertexBuffer(gVulkanContext.vertices2, vertexBuffer2, vertexBufferMemory2);
	createIndexBuffer(gVulkanContext.indices2, indexBuffer2, indexBufferMemory2);
	createUniformBuffers(uniformBuffers2, uniformBuffersMemory2, uniformBuffersMapped2);
	gVulkanContext.vertexBuffer2 = vertexBuffer2;
	gVulkanContext.indexBuffer2 = indexBuffer2;
	gVulkanContext.uniformBuffers2 = uniformBuffers2;
	gVulkanContext.uniformBuffersMapped2 = uniformBuffersMapped2;

	//SKKYBOX
	createVertexBuffer(gVulkanContext.skyVertices, vertexBuffer3, vertexBufferMemory3);
	createIndexBuffer(gVulkanContext.skyIndices, indexBuffer3, indexBufferMemory3);
	createUniformBuffers(uniformBuffers3, uniformBuffersMemory3, uniformBuffersMapped3);
	gVulkanContext.vertexBuffer3 = vertexBuffer3;
	gVulkanContext.indexBuffer3 = indexBuffer3;
	gVulkanContext.uniformBuffers3 = uniformBuffers3;
	gVulkanContext.uniformBuffersMapped3 = uniformBuffersMapped3;
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

	for (size_t i = 0; i < gVulkanContext.MAX_FRAMES_IN_FLIGHT; i++)
	{
		vkDestroyBuffer(gVulkanContext.device, uniformBuffers2[i], nullptr);
		vkFreeMemory(gVulkanContext.device, uniformBuffersMemory2[i], nullptr);
	}
	vkDestroyBuffer(gVulkanContext.device, vertexBuffer2, nullptr);
	vkFreeMemory(gVulkanContext.device, vertexBufferMemory2, nullptr);
	vkDestroyBuffer(gVulkanContext.device, indexBuffer2, nullptr);
	vkFreeMemory(gVulkanContext.device, indexBufferMemory2, nullptr);

	//SKYBOX
	for (size_t i = 0; i < gVulkanContext.MAX_FRAMES_IN_FLIGHT; i++)
	{
		vkDestroyBuffer(gVulkanContext.device, uniformBuffers3[i], nullptr);
		vkFreeMemory(gVulkanContext.device, uniformBuffersMemory3[i], nullptr);
	}
	vkDestroyBuffer(gVulkanContext.device, vertexBuffer3, nullptr);
	vkFreeMemory(gVulkanContext.device, vertexBufferMemory3, nullptr);
	vkDestroyBuffer(gVulkanContext.device, indexBuffer3, nullptr);
	vkFreeMemory(gVulkanContext.device, indexBufferMemory3, nullptr);
}

void CreateBuffer::createVertexBuffer(std::vector<Vertex>& vertices, VkBuffer& vertexBuffer, VkDeviceMemory& vertexBufferMemory)
{
	VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;

	createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory, "Vertex Buffer Staging");

	void* data;
	vkMapMemory(gVulkanContext.device, stagingBufferMemory, 0, bufferSize, 0, &data);
	memcpy(data, vertices.data(), (size_t)bufferSize);
	vkUnmapMemory(gVulkanContext.device, stagingBufferMemory);

	createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer, vertexBufferMemory, "Vertex Buffer");

	copyBuffer(stagingBuffer, vertexBuffer, bufferSize);

	vkDestroyBuffer(gVulkanContext.device, stagingBuffer, nullptr);
	vkFreeMemory(gVulkanContext.device, stagingBufferMemory, nullptr);
}

void CreateBuffer::createIndexBuffer(std::vector<uint32_t>& indices, VkBuffer& indexBuffer, VkDeviceMemory& indexBufferMemory)
{
	VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();

	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;
	createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory, "Index Buffer Staging");

	void* data;
	vkMapMemory(gVulkanContext.device, stagingBufferMemory, 0, bufferSize, 0, &data);
	memcpy(data, indices.data(), (size_t)bufferSize);
	vkUnmapMemory(gVulkanContext.device, stagingBufferMemory);

	createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, indexBufferMemory, "Index Buffer");

	copyBuffer(stagingBuffer, indexBuffer, bufferSize);

	vkDestroyBuffer(gVulkanContext.device, stagingBuffer, nullptr);
	vkFreeMemory(gVulkanContext.device, stagingBufferMemory, nullptr);
}

void CreateBuffer::createUniformBuffers(std::vector<VkBuffer>& uniformBuffers, std::vector<VkDeviceMemory>& uniformBuffersMemory, std::vector<void*>& uniformBuffersMapped)
{
	VkDeviceSize bufferSize = sizeof(UniformBufferObject);

	uniformBuffers.resize(gVulkanContext.MAX_FRAMES_IN_FLIGHT);
	uniformBuffersMemory.resize(gVulkanContext.MAX_FRAMES_IN_FLIGHT);
	uniformBuffersMapped.resize(gVulkanContext.MAX_FRAMES_IN_FLIGHT);

	for (size_t i = 0; i < gVulkanContext.MAX_FRAMES_IN_FLIGHT; i++)
	{
		createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffers[i], uniformBuffersMemory[i], "Uniform Buffer");

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

void CreateBuffer::copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, uint32_t layerCount)
{
	VkCommandBuffer commandBuffer = CreateCommandBuffer::beginSingleTimeCommands();

	VkDeviceSize faceSize = static_cast<VkDeviceSize>(width) * height * 4;

	std::vector<VkBufferImageCopy> regions(layerCount);
	for (uint32_t i = 0; i < layerCount; ++i) {
		VkBufferImageCopy& region = regions[i];
		region.bufferOffset = faceSize * i;
		region.bufferRowLength = 0;
		region.bufferImageHeight = 0;

		region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		region.imageSubresource.mipLevel = 0;
		region.imageSubresource.baseArrayLayer = i;
		region.imageSubresource.layerCount = 1;

		region.imageOffset = { 0, 0, 0 };
		region.imageExtent = { width, height, 1 };
	}

	vkCmdCopyBufferToImage(commandBuffer, buffer, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, static_cast<uint32_t>(regions.size()), regions.data());

	CreateCommandBuffer::endSingleTimeCommands(commandBuffer);
}

void CreateBuffer::createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory, std::string typeOfBuffer)
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
		throw std::runtime_error("!-- Failed to allocate buffer memory --! : " + typeOfBuffer);
	}

	vkBindBufferMemory(gVulkanContext.device, buffer, bufferMemory, 0);
}

void CreateBuffer::updateUniformBuffer(uint32_t currentImage, std::vector<void*> uniformBuffersMapped, float translate)
{
	//static auto startTime = std::chrono::high_resolution_clock::now();
	//auto currentTime = std::chrono::high_resolution_clock::now();

	//float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
	//ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	UniformBufferObject ubo{};
	//ubo.model = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, -1.0f, 1.0f));
	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, -translate));
	transform = glm::rotate(transform, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	ubo.model = transform;
	//ubo.model = glm::mat4(1.0f);
	ubo.view = glm::lookAt(gVulkanContext.camera.position, gVulkanContext.camera.position + gVulkanContext.camera.front, glm::vec3(0.0f, 1.0f, 0.0f));
	ubo.proj = glm::perspective(glm::radians(45.0f), gVulkanContext.swapchainExtent.width / (float)gVulkanContext.swapchainExtent.height, 0.1f, 100.0f);
	ubo.proj[1][1] *= -1;
	memcpy(uniformBuffersMapped[currentImage], &ubo, sizeof(ubo));
}

void CreateBuffer::updateUniformBufferForSkybox(uint32_t currentImage, std::vector<void*> uniformBuffersMapped)
{
	UniformBufferObject ubo{};

	glm::mat4 cameraView = glm::lookAt(gVulkanContext.camera.position, gVulkanContext.camera.position + gVulkanContext.camera.front, gVulkanContext.camera.up);

	glm::mat4 cameraProj = glm::perspective(glm::radians(45.0f), gVulkanContext.swapchainExtent.width / (float)gVulkanContext.swapchainExtent.height, 0.1f, 100.0f);

	ubo.model = glm::mat4(1.0f);
	ubo.view = glm::mat4(glm::mat3(cameraView));
	ubo.proj = cameraProj;
	ubo.proj[1][1] *= -1;

	memcpy(uniformBuffersMapped[currentImage], &ubo, sizeof(ubo));
}
