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

	VkBuffer vertexBuffer2;
	VkDeviceMemory vertexBufferMemory2;
	VkBuffer indexBuffer2;
	VkDeviceMemory indexBufferMemory2;

	std::vector<VkBuffer> uniformBuffers2;
	std::vector<VkDeviceMemory> uniformBuffersMemory2;
	std::vector<void*> uniformBuffersMapped2;

	VkBuffer vertexBuffer3;
	VkDeviceMemory vertexBufferMemory3;
	VkBuffer indexBuffer3;
	VkDeviceMemory indexBufferMemory3;

	std::vector<VkBuffer> uniformBuffers3;
	std::vector<VkDeviceMemory> uniformBuffersMemory3;
	std::vector<void*> uniformBuffersMapped3;

	void createVertexBuffer(std::vector<Vertex>& vertices, VkBuffer& vertexBuffer, VkDeviceMemory& vertexBufferMemory);
	void createIndexBuffer(std::vector<uint32_t>& indices, VkBuffer& indexBuffer, VkDeviceMemory& indexBufferMemory);
	void createUniformBuffers(std::vector<VkBuffer>& uniformBuffers, std::vector<VkDeviceMemory>& uniformBuffersMemory, std::vector<void*>& uniformBuffersMapped);

	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

public:

	void gCreateBuffer();
	void cleanUp();

	static void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory, std::string typeOfBuffer);
	static void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, uint32_t layerCount);
	static void updateUniformBuffer(uint32_t currentImage, std::vector<void*> uniformBuffersMapped, float translate);
	static void updateUniformBufferForSkybox(uint32_t currentImage, std::vector<void*> uniformBuffersMapped);
};