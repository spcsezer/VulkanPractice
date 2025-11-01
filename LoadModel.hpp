#pragma once

#include"Vertex.hpp"
#include"GlobalState.hpp"

class LoadModel
{
private:

	const std::string MODEL_PATH = "objects/viking_room.obj";

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	void loadModel();

public:

	void gLoadModel();
};