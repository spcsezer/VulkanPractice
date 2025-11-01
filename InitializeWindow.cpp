#include "InitializeWindow.hpp"

InitializeWindow::InitializeWindow()
{
	initializeWindow();
	gVulkanContext.window = window;
	gVulkanContext.frameBufferResized = frameBufferResized;
}

InitializeWindow::~InitializeWindow()
{
	glfwDestroyWindow(window);
	glfwTerminate();
	gVulkanContext.window = nullptr;
}

void InitializeWindow::initializeWindow()
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(1368, 760, "Vulkan Practice", nullptr, nullptr);

	glfwSetWindowUserPointer(window, &gVulkanContext);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouseCallBack);

	glfwSetFramebufferSizeCallback(window, framebufferResizeCallBack);
}

void InitializeWindow::framebufferResizeCallBack(GLFWwindow* window, int width, int height)
{
	auto app = reinterpret_cast<InitializeWindow*>(glfwGetWindowUserPointer(window));
	app->frameBufferResized = true;
}

void InitializeWindow::mouseCallBack(GLFWwindow* window, double xpos, double ypos)
{
	VulkanContext* app = reinterpret_cast<VulkanContext*>(glfwGetWindowUserPointer(window));
	if (app)
		app->camera.handleMouse(xpos, ypos);
}