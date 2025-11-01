#pragma once

#include"GlobalState.hpp"

class CreateDescriptorSetLayout
{
private:

	VkDescriptorSetLayout descriptorSetLayout;

	void createDescriptorSetLayout();

public:

	void gCreateDescriptorSetLayout();
	void cleanUp();
};