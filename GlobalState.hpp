#pragma once

#include <gtc/matrix_transform.hpp>

#include <stdexcept>
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
#include <fstream>
#include <array>
#include <unordered_map>

#include"Vertex.hpp"
#include "Camera.hpp"
#include"Object.hpp"
#include"Texture.hpp"

struct Vertex;

class ValidationLayers;

struct VulkanContext
{
	GLFWwindow* window = VK_NULL_HANDLE;

	ValidationLayers* validationLayers = VK_NULL_HANDLE;

	VkInstance instance = VK_NULL_HANDLE;

	VkSurfaceKHR surface = VK_NULL_HANDLE;

	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkSampleCountFlagBits msaaSamples = VK_SAMPLE_COUNT_1_BIT;

	CameraNew camera;

	const std::vector<const char*> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

	VkDevice device = VK_NULL_HANDLE;
	VkQueue graphicsQueue = VK_NULL_HANDLE;
	VkQueue presentQueue = VK_NULL_HANDLE;

	std::vector<VkImage> swapchainImages;
	VkSwapchainKHR swapchain = VK_NULL_HANDLE;
	VkFormat swapchainImageFormat;
	VkExtent2D swapchainExtent;

	std::vector<VkImageView> swapchainImageViews;

	VkRenderPass renderPass;

	VkDescriptorSetLayout descriptorSetLayout;
	VkDescriptorSetLayout descriptorSetLayout2;
	VkDescriptorSetLayout descriptorSetLayout3;

	std::vector<VkDescriptorSet> descriptorSets;
	std::vector<VkDescriptorSet> descriptorSets2;
	std::vector<VkDescriptorSet> descriptorSets3;

	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;

	VkPipelineLayout skyboxPipelineLayout;
	VkPipeline skyboxGraphicsPipeline;

	std::vector<VkFramebuffer> swapchainFrameBuffers;

	VkCommandPool commandPool;

	std::vector<VkCommandBuffer> commandBuffers;

	VkImage colorImage;
	VkDeviceMemory colorImageMemory;
	VkImageView colorImageView;

	VkImage depthImage;
	VkDeviceMemory depthImageMemory;
	VkImageView depthImageView;

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	std::vector<Vertex> vertices2;
	std::vector<uint32_t> indices2;

	std::vector<Vertex> skyVertices;
	std::vector<uint32_t> skyIndices;

	const int MAX_FRAMES_IN_FLIGHT = 2;
	bool frameBufferResized = false;

	VkBuffer vertexBuffer;
	VkBuffer indexBuffer;
	std::vector<VkBuffer> uniformBuffers;
	std::vector<void*> uniformBuffersMapped;

	VkBuffer vertexBuffer2;
	VkBuffer indexBuffer2;
	std::vector<VkBuffer> uniformBuffers2;
	std::vector<void*> uniformBuffersMapped2;

	VkBuffer vertexBuffer3;
	VkBuffer indexBuffer3;
	std::vector<VkBuffer> uniformBuffers3;
	std::vector<void*> uniformBuffersMapped3;

	/*
	VkImageView textureImageView;
	VkSampler textureSampler;

	VkImageView textureImageView2;
	VkSampler textureSampler2;

	//SKYBOX
	VkImageView rightSkyImageView;
	VkSampler rightSkySampler;

	VkImageView leftSkyImageView;
	VkSampler leftSkySampler;
	//~SKYBOX
	*/
	uint32_t currentFrame = 0;

	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> inFlightFences;

	#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else
	const bool enableValidationLayers = true;
#endif

	std::vector<Object> objects;
	
	std::vector<VkDescriptorSetLayout> descriptorSetLayouts;

	std::vector<Texture> textures;
};

extern VulkanContext gVulkanContext;