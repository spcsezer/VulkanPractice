#pragma once

#include"GlobalState.hpp"

class ValidationLayers
{
private:

	const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };

	VkDebugUtilsMessengerEXT debugMessenger;

public:

	const std::vector<const char*>& getValidationLayers() const
	{
		return validationLayers;
	}
	
	bool getEnableValidationLayers() const
	{
		return gVulkanContext.enableValidationLayers;
	}

	bool checkValidationLayerSupport();

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallBack(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData
	);

	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

	void setupDebugMessenger();

	VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

	void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
	
	void gValidationLayers();
	void cleanUp();
};

/*
* if (enableValidationLayers) {
            DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
        }
*/