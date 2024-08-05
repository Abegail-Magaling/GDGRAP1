#include "Light.h"

Light::Light()
{
	
	this->lightPos = glm::vec3(4, -5, 0);
	this->lightColor = glm::vec3(1.f, 1.f, 1.f);
	this->ambientColor = lightColor;
	this->brightness = 1;
	this->ambientStr = 0.5f;
	this->specStr = 10.0f;
	this->specPhong = 15.f;
}

float Light::getBrightness()
{
	return this->brightness;
}

float Light::getAmbientStr()
{
	return this->ambientStr;
}

void Light::setBrightness(float Brightness)
{
	this->brightness += Brightness;
}

void Light::setAmbientStr(float AmbientStr)
{
	this->ambientStr += AmbientStr;
}

void Light::lightInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		setBrightness(1.0);
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		setBrightness(-1.0);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		setAmbientStr(-0.2);
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		setAmbientStr(0.2);
	}
}
