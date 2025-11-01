#include "CreateSurface.hpp"

void CreateSurface::gCreateSurface()
{
	createSurface();
	gVulkanContext.surface = surface;
}

void CreateSurface::cleanUp()
{
	vkDestroySurfaceKHR(gVulkanContext.instance, surface, nullptr);
	gVulkanContext.surface = nullptr;
}

void CreateSurface::createSurface()
{
	if (glfwCreateWindowSurface(gVulkanContext.instance, gVulkanContext.window, nullptr, &surface) != VK_SUCCESS)
	{
		throw std::runtime_error("!-- Failed to create window surface --!");
	}
}
