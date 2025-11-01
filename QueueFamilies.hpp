#pragma once

#include"GlobalState.hpp"

#include<optional>
#include<vector>

struct QueueFamilyIndices
{
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete()
	{
		return graphicsFamily.has_value() && presentFamily.has_value();
	}

	static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
};