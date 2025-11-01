#pragma once

#define GLFW_INCLUDE_VULKAN
#include<GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include<glm.hpp>

struct CameraNew
{
	glm::vec3 velocity{ 0.0f };
	glm::vec3 position{ 0.0f };
	glm::vec3 front{ 0.0f, 0.0f, -1.0f };

	float pitch = 0.0f;

	float yaw = -90.0f;

	float sensitivity = 0.1f;

	bool firstMouse = false;
	double lastX = 0.0;
	double lastY = 0.0;

	void handleKey(GLFWwindow* window);
	void handleMouse(double xpos, double ypos);

	void update();
};