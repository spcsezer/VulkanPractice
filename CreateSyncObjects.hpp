#pragma once

#include"GlobalState.hpp"

class CreateSyncObjects
{
private:

	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> inFlightFences;

	void createSyncObjects();

public:

	void gCreateSyncObjects();
	void cleanUp();
};