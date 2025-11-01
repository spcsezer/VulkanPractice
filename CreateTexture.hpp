#pragma once

#include"GlobalState.hpp"
#include"CreateResources.hpp"
#include"CreateBuffer.hpp"
#include"CreateImageViews.hpp"
#include"CreateCommandBuffer.hpp"

class CreateTexture
{
private:

	const std::string MODEL_TEXTURE_PATH = "objects/viking_room.png";
	uint32_t mipLevels;
	VkImage textureImage;
	VkImageView textureImageView;
	VkDeviceMemory textureImageMemory;
	VkSampler textureSampler;

	const std::string MODEL_TEXTURE_PATH2 = "objects/viking_room.png";
	uint32_t mipLevels2;
	VkImage textureImage2;
	VkImageView textureImageView2;
	VkDeviceMemory textureImageMemory2;
	VkSampler textureSampler2;

	void createTextureImage(const std::string& MODEL_TEXTURE_PATH, uint32_t& mipLevels, VkImage& textureImage, VkDeviceMemory& textureImageMemory);
	void createTextureImageView(uint32_t& mipLevels, VkImage& textureImage, VkImageView& textureImageView);
	void createTextureSampler(uint32_t& mipLevels, VkSampler& textureSampler);

public:

	void gCreateTexture();
	void cleanUp();

	static void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);
};