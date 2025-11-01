#pragma once

#include"GlobalState.hpp"
#include"CreateResources.hpp"
#include"UniformBufferObject.hpp"
#include"CreateCommandBuffer.hpp"
#include"Vertex.hpp"

class CreateBuffer
{
private:

	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;
	VkBuffer indexBuffer;
	VkDeviceMemory indexBufferMemory;

	std::vector<VkBuffer> uniformBuffers;
	std::vector<VkDeviceMemory> uniformBuffersMemory;
	std::vector<void*> uniformBuffersMapped;

	void createVertexBuffer();
	void createIndexBuffer();
	void createUniformBuffers();

	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

public:

	void gCreateBuffer();
	void cleanUp();

	static void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	static void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
	static void updateUniformBuffer(uint32_t currentImage);
};