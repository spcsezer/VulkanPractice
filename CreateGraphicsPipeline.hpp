#pragma once

#include"Vertex.hpp"
#include"GlobalState.hpp"

class CreateGraphicsPipeline
{
private:

	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;
	const char* vertexShaderFile = "shaders/vert.spv";
	const char* fragmentShaderFile = "shaders/frag.spv";

	VkPipelineLayout skyboxPipelineLayout;
	VkPipeline skyboxGraphicsPipeline;
	const char* skyboxVertexShaderFile = "shaders/skyboxVert.spv";
	const char* skyboxFragmentShaderFile = "shaders/skyboxFrag.spv";

	void createGraphicsPipeline(const char* vertexShaderFile, const char* fragmentShaderFile, VkPipelineLayout& pipelineLayout, VkPipeline& graphicsPipeline, VkDescriptorSetLayout& descriptorSetLayout, VkCullModeFlags cullModeFlags, VkBool32 depthWriteEnable, VkCompareOp depthCompareOp);

	std::vector<char> readFile(const std::string& fileName);
	VkShaderModule createShaderModule(const std::vector<char>& code);

public:

	void gCreateGraphicsPipeline();
	void cleanUp();
};