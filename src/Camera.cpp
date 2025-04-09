#include "Camera.h"

namespace Engine {
	Camera::Camera(int _width, int _height, glm::vec3 _position)
	{
		width = _width;
		height = _height;
		position = _position;
	}

	void Camera::UpdateMatrix(float _FOVdeg, float _nearPlane, float _farPlane)
	{
		// Initializes matrices since otherwise they will be the null matrix
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		// Makes camera look in the right direction from the right position
		view = glm::lookAt(position, position + orientation, up);
		// Adds perspective to the scene
		projection = glm::perspective(glm::radians(_FOVdeg), (float)width / height, _nearPlane, _farPlane);

		// Sets new camera matrix
		cameraMatrix = projection * view;
	}

	void Camera::Matrix(Shader& _shader, const char* _uniform)
	{
		// Exports camera matrix
		glUniformMatrix4fv(glGetUniformLocation(_shader.GetID(), _uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
	}

	void Camera::Inputs(GLFWwindow* _window)
	{
		if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS) {
			position += speed * orientation;
		}
		if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS) {
			position -= speed * orientation;
		}
		if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS) {
			position -= speed * glm::normalize(glm::cross(orientation, up));
		}
		if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS) {
			position += speed * glm::normalize(glm::cross(orientation, up));
		}
		if (glfwGetKey(_window, GLFW_KEY_Q) == GLFW_PRESS) {
			position -= speed * up;
		}
		if (glfwGetKey(_window, GLFW_KEY_E) == GLFW_PRESS) {
			position += speed * up;
		}
		if (glfwGetKey(_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
			speed = 0.4f;
		}
		else if (glfwGetKey(_window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
			speed = 0.1f;
		}

		if (glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

			if (isFirstClick)
			{
				glfwSetCursorPos(_window, (width / 2), (height / 2));
				isFirstClick = false;
			}

			double mouseX, mouseY;
			glfwGetCursorPos(_window, &mouseX, &mouseY);

			float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
			float rotY = sensitivity * (float)(mouseX - (height / 2)) / height;

			glm::vec3 new_orientation = glm::rotate(orientation, glm::radians(-rotX), glm::normalize(glm::cross(orientation, up)));

			if (!(glm::angle(new_orientation, up) <= glm::radians(5.0f)) || (glm::angle(new_orientation, -up) <= glm::radians(5.0f))) {
				orientation = new_orientation;
			}

			orientation = glm::rotate(orientation, glm::radians(-rotY), up);

			glfwSetCursorPos(_window, (width / 2), (height / 2));
		}
		else if (glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
			glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			isFirstClick = true;
		}
	}

}