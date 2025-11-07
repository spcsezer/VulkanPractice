#pragma once

#include"CreateResources.hpp"
#include"CreateBuffer.hpp"
#include"CreateImageViews.hpp"
#include"CreateCommandBuffer.hpp"

class CreateTexture
{
private:
	const std::string MODEL_TEXTURE_PATH = "objects/viking_room.png";
	const std::string MODEL_TEXTURE_PATH2 = "objects/viking_room.png";
	const std::string SKY_TEXTURE_PATH = "textures/skybox";
	
	void createTextureImage(const std::string& MODEL_TEXTURE_PATH, uint32_t& mipLevels, VkImage& textureImage, VkDeviceMemory& textureImageMemory, uint32_t arrayLayers, VkImageCreateFlags flags);
	void createTextureImageView(uint32_t& mipLevels, VkImage& textureImage, VkImageView& textureImageView, VkImageViewType viewType, uint32_t layerCount);
	void createTextureSampler(uint32_t& mipLevels, VkSampler& textureSampler, VkSamplerAddressMode addressMode, VkCompareOp compareOp);

public:
	void gCreateTexture();
	void pCreateTexture(std::string TEXTURE_PATH, uint32_t& mipLevels, VkImage& textureImage, VkImageView& textureImageView, VkDeviceMemory& textureImageMemory, VkSampler& textureSampler, uint32_t arrayLayers, VkImageCreateFlags flags, VkImageViewType viewType, uint32_t layerCount, VkSamplerAddressMode addressMode, VkCompareOp compareOp);
	void cleanUp();

	static void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);
};