#pragma once

#include"GlobalState.hpp"

class CreateFrameBuffers
{
private:
	std::vector<VkFramebuffer> swapchainFrameBuffers;

	void createFrameBuffers();

public:

	void gCreateFrameBuffers();
	void cleanUp();
};