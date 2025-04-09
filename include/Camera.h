#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm.hpp>
#include<gtc/matrix_transform.hpp>
#include<gtc/type_ptr.hpp>
#include<gtx/rotate_vector.hpp>
#include<gtx/vector_angle.hpp>

#include "Shader.h"


namespace Engine {

	class Camera
	{
	public:
		glm::vec3 position;
		glm::vec3 orientation = glm::vec3(0.f, 0.f, -1.f);
		glm::vec3 up = glm::vec3(0.f, 1.f, 0.f);
		glm::mat4 cameraMatrix = glm::mat4(1.0f);

		int width;
		int height;

		bool isFirstClick = true;

		float speed = 0.1f;
		float sensitivity = 100.f;

		Camera(int _width, int _height, glm::vec3 _position);

		void UpdateMatrix(float _FOVdeg, float _nearPlane, float _farPlane);
		void Matrix(Shader& _shader, const char* _uniform);
		void Inputs(GLFWwindow* _window);
	};

}