#ifndef MODEL3D_H
#define MODEL3D_H

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

class Model3D
{
    private:
        //Position of model
        float pos_x = 0.0f;
        float pos_y = -2.0f;
        float pos_z = -5.0f;
        std::vector<glm::vec3> positions;

        //Scale of model
        float scale = 0.3f;

        float axis_x = 0.0f;
        float axis_y = 1.0f;
        float axis_z = 0.0f;

        float theta = 0.0f;

		double lastGenerationTime; //keeps track of the time elapsed since the generation of the last model

    public:
        //Constructor
        Model3D();

        //Matrix Initialization
		glm::mat4 TranslationMatrix(glm::mat4 identity_matrix, const glm::vec3 position) const;
		glm::mat4 ScaleMatrix(glm::mat4 identity_matrix) const;
		glm::mat4 RotationMatrix(glm::mat4 identity_matrix) const;

        //other functions
        void cleanup(GLFWwindow* window, GLuint VAO, GLuint VBO, GLuint EBO, GLuint vertexShader, GLuint fragmentShader, GLuint shaderProg) const;
        void draw(GLuint shaderProg, GLuint VAO, std::vector<unsigned int> mesh_indices, const glm::mat4 viewMatrix, const glm::mat4 identity_matrix, const glm::mat4 projection_matrix, const glm::vec3 position) const;
        void drawWithTexture(GLuint shaderProg, GLuint VAO, std::vector<unsigned int> mesh_indices, const glm::mat4 viewMatrix, const glm::mat4 identity_matrix, const glm::mat4 projection_matrix, const glm::vec3 position) const;
        void addModel(const glm::vec3& position);

    public:
        const std::vector<glm::vec3>& getPositions() const;
};

#endif