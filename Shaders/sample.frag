#version 330 core

out vec4 FragColor; // Returns a color

uniform sampler2D tex0;

in vec2 texCoord;

in vec3 normCoord;

in vec3 fragPos;

uniform vec3 lightPos; //position of light

uniform vec3 lightColor; //color of light

uniform float ambientStr;

uniform vec3 ambientColor;

uniform vec3 CameraPos;

uniform float specStr;

uniform float specPhong;

uniform float brightness; //added parameter for brightness



//Simple shader that colors the model 
void main()
{
	vec3 normal = normalize(normCoord);
	vec3 lightDir = normalize(lightPos - fragPos);

	float distance = length(lightPos - fragPos); //calculates the distance between the lightsource and object
	float intensity = 1.0 / (1.0 + 0.1 * distance + 0.01 * distance * distance); //calculates the light intensity as the distance from the light source increases.

	float diff = max(dot(normal, lightDir), 0.0); //apply diffuse formula
	vec3 diffuse = diff * lightColor * brightness * intensity; //add the brighness and intensity
	vec3 ambientCol = ambientColor * ambientStr * brightness; //add brightness

	vec3 viewDir = normalize(CameraPos - fragPos);

	vec3 reflectDir = reflect(-lightDir, normal);

	float spec = pow(max(dot(reflectDir, viewDir), 0.1), specPhong);

	vec3 specColor = spec * specStr * lightColor * brightness; //add brightness


	//				  R   G   B  a  Ranges from 0->1
	//FragColor = vec4(0.60f, 0.40f, 1.0f, 1.0f); //Sets the color of the fragment

	FragColor = vec4(specColor + diffuse + ambientCol, 1.0) * texture(tex0, texCoord);
}