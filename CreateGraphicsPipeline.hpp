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

	void createGraphicsPipeline(const char* vertexShaderFile, const char* fragmentShaderFile, VkPipelineLayout& pipelineLayout, VkPipeline& graphicsPipeline, VkDescriptorSetLayout& descriptorSetLayout);

	std::vector<char> readFile(const std::string& fileName);
	VkShaderModule createShaderModule(const std::vector<char>& code);

public:

	void gCreateGraphicsPipeline();
	void cleanUp();
};