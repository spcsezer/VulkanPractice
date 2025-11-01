#define GLFW_INCLUDE_VULKAN
#include<GLFW/glfw3.h>

#include<vector>

struct Object
{
	VkBuffer vertexBuffer;
	VkBuffer indexBuffer;
	std::vector<uint32_t> indices;
	std::vector<VkDescriptorSet> descriptorSets;
};