#include "CreateDescriptorSetLayout.hpp"

void CreateDescriptorSetLayout::gCreateDescriptorSetLayout()
{
	createDescriptorSetLayout(descriptorSetLayout);
	gVulkanContext.descriptorSetLayout = descriptorSetLayout;

	createDescriptorSetLayout(descriptorSetLayout2);
	gVulkanContext.descriptorSetLayout2 = descriptorSetLayout2;

	gVulkanContext.descriptorSetLayouts.push_back(descriptorSetLayout);
	gVulkanContext.descriptorSetLayouts.push_back(descriptorSetLayout2);
}

void CreateDescriptorSetLayout::cleanUp()
{
	vkDestroyDescriptorSetLayout(gVulkanContext.device, descriptorSetLayout, nullptr);
	gVulkanContext.descriptorSetLayout = nullptr;

	vkDestroyDescriptorSetLayout(gVulkanContext.device, descriptorSetLayout2, nullptr);
	gVulkanContext.descriptorSetLayout2 = nullptr;
}

void CreateDescriptorSetLayout::createDescriptorSetLayout(VkDescriptorSetLayout& descriptorSetLayout)
{
	VkDescriptorSetLayoutBinding uboLayoutBinding{};
	uboLayoutBinding.binding = 0;
	uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	uboLayoutBinding.descriptorCount = 1;
	uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
	uboLayoutBinding.pImmutableSamplers = nullptr;

	VkDescriptorSetLayoutBinding samplerLayoutBinding{};
	samplerLayoutBinding.binding = 1;
	samplerLayoutBinding.descriptorCount = 1;
	samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	samplerLayoutBinding.pImmutableSamplers = nullptr;
	samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

	std::array<VkDescriptorSetLayoutBinding, 2> bindings = { uboLayoutBinding, samplerLayoutBinding };

	VkDescriptorSetLayoutCreateInfo layoutInfo{};
	layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
	layoutInfo.pBindings = bindings.data();

	if (vkCreateDescriptorSetLayout(gVulkanContext.device, &layoutInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS)
	{
		throw std::runtime_error("!-- Failed to create descriptor set layout --!");
	}
}