#pragma once

#include"Vertex.hpp"
#include"GlobalState.hpp"

class CreateGraphicsPipeline
{
private:

	VkPipelineLayout pipelineLayout;

	VkPipeline graphicsPipeline;

	void createGraphicsPipeline();

	std::vector<char> readFile(const std::string& fileName);
	VkShaderModule createShaderModule(const std::vector<char>& code);

public:

	void gCreateGraphicsPipeline();
	void cleanUp();
};