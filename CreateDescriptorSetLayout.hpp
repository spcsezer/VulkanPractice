#pragma once

#include"GlobalState.hpp"

class CreateDescriptorSetLayout
{
private:

	VkDescriptorSetLayout descriptorSetLayout;
	VkDescriptorSetLayout descriptorSetLayout2;
	VkDescriptorSetLayout descriptorSetLayout3;

	void createDescriptorSetLayout(VkDescriptorSetLayout& descriptorSetLayout);

public:

	void gCreateDescriptorSetLayout();
	void cleanUp();
};