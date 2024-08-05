#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(GLuint shaderProg)
{
    GLuint lightAddress = glGetUniformLocation(shaderProg, "lightPos");
    glUniform3fv(lightAddress, 1, glm::value_ptr(this->lightPos));

    GLuint lightColorAdd = glGetUniformLocation(shaderProg, "lightColor");
    glUniform3fv(lightColorAdd, 1, glm::value_ptr(this->lightColor));

    GLuint ambientStrAdd = glGetUniformLocation(shaderProg, "ambientStr");
    glUniform1f(ambientStrAdd, this->ambientStr);

    GLuint ambientColorAdd = glGetUniformLocation(shaderProg, "ambientColor");
    glUniform3fv(ambientColorAdd, 1, glm::value_ptr(this->ambientColor));

    GLuint specStrAdd = glGetUniformLocation(shaderProg, "specStr");
    glUniform1f(specStrAdd, this->specStr);

    GLuint specPhongAdd = glGetUniformLocation(shaderProg, "specPhong");
    glUniform1f(specPhongAdd, this->specPhong);

    GLuint brightnessAdd = glGetUniformLocation(shaderProg, "brightness");
    glUniform1f(brightnessAdd, this->brightness);
}

DirectionalLight::DirectionalLight()
{

}
