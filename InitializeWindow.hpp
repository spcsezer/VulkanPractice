#pragma once

#include"GlobalState.hpp"

class InitializeWindow
{
private:

	GLFWwindow* window;

	bool frameBufferResized = false;

	void initializeWindow();

	static void framebufferResizeCallBack(GLFWwindow* window, int width, int height);

	static void mouseCallBack(GLFWwindow* window, double xpos, double ypos);

public:

	InitializeWindow();
	~InitializeWindow();
};

