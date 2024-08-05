#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include "Light.h"

class DirectionalLight : public Light
{

	public:
		DirectionalLight(GLuint shaderProg);
		DirectionalLight();

	public:
		/*void renderLight();*/
};

#endif // !
