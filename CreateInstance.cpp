#include "CreateInstance.hpp"
#include "ValidationLayers.hpp"

void CreateInstance::gCreateInstance()
{
	createInstance();
	gVulkanContext.instance = instance;
}

void CreateInstance::cleanUp()
{
	vkDestroyInstance(instance, nullptr);
	gVulkanContext.instance = nullptr;
}

void CreateInstance::createInstance()
{
	if (gVulkanContext.validationLayers->getEnableValidationLayers() && !gVulkanContext.validationLayers->checkValidationLayerSupport()) {
		throw std::runtime_error("validation layers requested, but not available!");
	}

	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Vulkan Practice";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "No Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_4;

	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	auto extensions = getRequiredExtensions();
	createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
	createInfo.ppEnabledExtensionNames = extensions.data();

	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
	if (gVulkanContext.validationLayers->getEnableValidationLayers()) {
		createInfo.enabledLayerCount = static_cast<uint32_t>(gVulkanContext.validationLayers->getValidationLayers().size());
		createInfo.ppEnabledLayerNames = gVulkanContext.validationLayers->getValidationLayers().data();

		gVulkanContext.validationLayers->populateDebugMessengerCreateInfo(debugCreateInfo);
		createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
	}
	else {
		createInfo.enabledLayerCount = 0;

		createInfo.pNext = nullptr;
	}

	if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
		throw std::runtime_error("failed to create instance!");
	}
}

std::vector<const char*> CreateInstance::getRequiredExtensions()
{
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

	if (gVulkanContext.validationLayers->getEnableValidationLayers())
	{
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}
	return extensions;
}