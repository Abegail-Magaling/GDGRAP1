#ifndef LIGHT_H
#define LIGHT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>

class Light {
	protected:
		glm::vec3 lightPos;
		glm::vec3 lightColor;
		glm::vec3 ambientColor;
		float specStr;
		float specPhong;
		float brightness;
		float ambientStr;

	public:
		Light();

	public:
		/*virtual void renderLight() = 0;*/


	public:
		float getBrightness();
		float getAmbientStr();

		void setBrightness(float Brightness);
		void setAmbientStr(float AmbientStr);

		void lightInput(GLFWwindow* window);
};

#endif // !