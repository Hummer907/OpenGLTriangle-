#include "Camera.h"
#include "shaderClass.h"

Camera::Camera(int width, int height, glm::vec3 position) {
	Camera::width = width;
	Camera::height = height;
	Position = position;
}


void Camera::Matrix(Shader& shader, const char* uniform)
{
	// Exports camera matrix
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
	glEnable(GL_DEPTH_TEST);
}

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	// Initializes matrices since otherwise they will be the null matrix
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	// Makes camera look in the right direction from the right position
	view = glm::lookAt(Position, Position + Orientation, Up);
	
	// Adds perspective to the scene
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

	// Sets new camera matrix
	cameraMatrix = projection * view * model;
}

void Camera::Inputs(GLFWwindow* window) {
	static float rotation = 0.0f;
	
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Position += speed * Orientation;
		
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position += speed * -glm::normalize(glm::cross(Orientation, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Position += speed * -Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position += speed * glm::normalize(glm::cross(Orientation, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		Position += speed * Up;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		Position += speed * -Up;
	}
	float angle = glm::radians(rotation);  // Convert the turn angle to radians
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		rotation += 0.00001f;
		glm::mat4 rotationMatrix = glm::rotate(angle, Up);  // Create a rotation matrix around the up vector
		Orientation = glm::vec3(rotationMatrix * glm::vec4(Orientation, 0.0f));  // Apply the rotation to the orientation vector
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		rotation += 0.00001f;
		glm::mat4 rotationMatrix = glm::rotate(-angle, Up);  // Create a rotation matrix around the up vector
		Orientation = glm::vec3(rotationMatrix * glm::vec4(Orientation, 0.0f));  // Apply the rotation to the orientation vector
	}
	

	
	
	
	
	
	// Apply the rotation to the view matrix
	model = glm::rotate(view, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
}
