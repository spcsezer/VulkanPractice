#define GLFW_INCLUDE_VULKAN
#include<GLFW/glfw3.h>
#include<string>

struct Texture
{
private:
	std::string TEXTURE_PATH;
	uint32_t TextureMipLevels;
	VkImage TextureImage;
	VkImageView TextureImageView;
	VkDeviceMemory TextureImageMemory;
	VkSampler TextureSampler;

	//CREATE IMAGE
	uint32_t arrayLayers;
	VkImageCreateFlags flags;

	//CREATE IMAGE VIEW
	VkImageViewType viewType;
	uint32_t layerCount;

	//CREATE IMAGE SAMPLER
	VkSamplerAddressMode addressMode;
	VkCompareOp compareOp;

public:

	Texture(const std::string TEXTURE_PATH, uint32_t arrayLayers, VkImageCreateFlags flags, uint32_t layerCount, VkImageViewType viewType, VkSamplerAddressMode addressMode, VkCompareOp compareOp)
	{
		createTexture(TEXTURE_PATH, arrayLayers, flags, layerCount, viewType, addressMode, compareOp);
	}

	VkImageView& getTextureImageView()
	{
		return TextureImageView;
	}
	VkSampler& getTextureSampler()
	{
		return TextureSampler;
	}

	void createTexture(const std::string TEXTURE_PATH, uint32_t arrayLayers, VkImageCreateFlags flags, uint32_t layerCount, VkImageViewType viewType, VkSamplerAddressMode addressMode, VkCompareOp compareOp);
	void cleanTexture(VkDevice device)
	{
		vkDestroySampler(device, TextureSampler, nullptr);
		vkDestroyImageView(device, TextureImageView, nullptr);
		vkDestroyImage(device, TextureImage, nullptr);
		vkFreeMemory(device, TextureImageMemory, nullptr);
	}
};