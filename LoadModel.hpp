#pragma once

#include"Vertex.hpp"
#include"GlobalState.hpp"

class LoadModel
{
private:

	const std::string MODEL_PATH = "objects/viking_room.obj";
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	const std::string MODEL_PATH2 = "objects/viking_room.obj";
	std::vector<Vertex> vertices2;
	std::vector<uint32_t> indices2;

	void loadModel(const std::string& MODEL_PATH, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);

public:

	void gLoadModel();
};