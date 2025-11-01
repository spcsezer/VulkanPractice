#include "Camera.hpp"

void CameraNew::handleKey(GLFWwindow* window)
{
	velocity = glm::vec3(0.0f);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		velocity.z -= 1.0f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		velocity.z += 1.0f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		velocity.x -= 1.0f;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		velocity.x += 1.0f;

	if (glm::length(velocity) > 0.0f)
		velocity = glm::normalize(velocity);
}

void CameraNew::handleMouse(double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xOffset = xpos - lastX;
	float yOffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	xOffset *= sensitivity;
	yOffset *= sensitivity;

	yaw += xOffset;
	pitch += yOffset;

	if (pitch > 85.0f) pitch = 85.0f;
	if (pitch < -85.0f) pitch = -85.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(direction);
}

void CameraNew::update()
{
	glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));

	float speed = 0.00125f;
	position += (front * -velocity.z + right * velocity.x) * speed;
}