#pragma once

#include"GlobalState.hpp"
#include"UniformBufferObject.hpp"

class CreateDescriptorSets
{
private:

	VkDescriptorPool descriptorPool;
	std::vector<VkDescriptorSet> descriptorSets;

	VkDescriptorPool descriptorPool2;
	std::vector<VkDescriptorSet> descriptorSets2;

	VkDescriptorPool descriptorPool3;
	std::vector<VkDescriptorSet> descriptorSets3;

	void createDescriptorPool(VkDescriptorPool& descriptorPool);
	void createDescriptorSets(std::vector<VkBuffer>& uniformBuffers, VkImageView& textureImageView, VkSampler& textureSampler, std::vector<VkDescriptorSet>& descriptorSets, VkDescriptorSetLayout& descriptorSetLayout, VkDescriptorPool& descriptorPool);

public:

	void gCreateDescriptorSets();
	void cleanUp();
};