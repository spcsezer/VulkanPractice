#pragma once

#include"Engine.hpp"
#include"InitializeWindow.hpp"
#include"DrawFrame.hpp"

#include<chrono>
#include<thread>

void RunProgram()
{
	InitializeWindow initializeWindow;
	RunEngine();

    auto lastFrameTime = std::chrono::high_resolution_clock::now();

    while (!glfwWindowShouldClose(gVulkanContext.window))
    {
        auto frameStart = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> delta = frameStart - lastFrameTime;
        lastFrameTime = frameStart;
        float deltaTime = delta.count();

        glfwPollEvents();

        gVulkanContext.camera.handleKey(gVulkanContext.window);
        gVulkanContext.camera.update(deltaTime);

        drawFrame();

        auto frameEnd = std::chrono::high_resolution_clock::now();
        auto frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd - frameStart);
        const int targetFPS = 60;
        const int frameDelay = 1000 / targetFPS;

        if (frameTime.count() < frameDelay)
            std::this_thread::sleep_for(std::chrono::milliseconds(frameDelay - frameTime.count()));
    }

	vkDeviceWaitIdle(gVulkanContext.device);

	CleanEngine();
}