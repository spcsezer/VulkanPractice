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
	std::vector<VkDescriptorSet> descriptorSets;

	VkPipelineLayout pipelineLayout;

	VkPipeline graphicsPipeline;

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

	const int MAX_FRAMES_IN_FLIGHT = 2;
	bool frameBufferResized = false;

	VkBuffer vertexBuffer;
	VkBuffer indexBuffer;

	std::vector<VkBuffer> uniformBuffers;
	std::vector<void*> uniformBuffersMapped;

	VkImageView textureImageView;
	VkSampler textureSampler;

	uint32_t currentFrame = 0;

	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> inFlightFences;

	#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else
	const bool enableValidationLayers = true;
#endif
};

extern VulkanContext gVulkanContext;