#pragma once

#include"GlobalState.hpp"
#include"UniformBufferObject.hpp"

class CreateDescriptorSets
{
private:

	VkDescriptorPool descriptorPool;
	std::vector<VkDescriptorSet> descriptorSets;

	void createDescriptorPool();
	void createDescriptorSets();

public:

	void gCreateDescriptorSets();
	void cleanUp();
};