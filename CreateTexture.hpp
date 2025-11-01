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

	void createTextureImage();
	void createTextureImageView();
	void createTextureSampler();

public:

	void gCreateTexture();
	void cleanUp();

	static void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);
};