#pragma once

#include"Engine.hpp"
#include"InitializeWindow.hpp"
#include"DrawFrame.hpp"

void RunProgram()
{
	InitializeWindow initializeWindow;
	RunEngine();

	while (!glfwWindowShouldClose(gVulkanContext.window))
	{
		glfwPollEvents();

		gVulkanContext.camera.handleKey(gVulkanContext.window);
		gVulkanContext.camera.update();

		drawFrame();
	}
	vkDeviceWaitIdle(gVulkanContext.device);

	CleanEngine();
}