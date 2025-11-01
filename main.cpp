#include"Run.hpp"

int main()
{
	gVulkanContext.validationLayers = &validationLayers;
	try
	{
		RunProgram();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}