#include "Model3D.h"

Model3D::Model3D() {}


//sets the Position of the Model
glm::mat4 Model3D::TranslationMatrix(glm::mat4 identity_matrix, const glm::vec3 position) const {
	glm::mat4 Translation_Matrix = glm::translate(identity_matrix, position);
	return Translation_Matrix;
}

//sets the scale of the Model
glm::mat4 Model3D::ScaleMatrix(glm::mat4 identity_matrix) const {
	glm::mat4 Scale_Matrix = glm::scale(identity_matrix, glm::vec3(this->scale, this->scale, this->scale));
	return Scale_Matrix;
}

//sets the rotation of the model
glm::mat4 Model3D::RotationMatrix(glm::mat4 identity_matrix) const {
	glm::mat4 Rotation_Matrix = glm::rotate(identity_matrix, glm::radians(this->theta), glm::normalize(glm::vec3(this->axis_x, this->axis_y, this->axis_z)));
	return Rotation_Matrix;
}

// clean OpenGL resources and terminate GLFW
void Model3D::cleanup(GLFWwindow* window, GLuint VAO, GLuint VBO, GLuint EBO, GLuint vertexShader, GLuint fragmentShader, GLuint shaderProg) const
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteProgram(shaderProg);
	glfwDestroyWindow(window);
	glfwTerminate();
}

// Function to draw the model using OpenGL
void Model3D::draw(GLuint shaderProg, GLuint VAO, std::vector<unsigned int> mesh_indices, const glm::mat4 viewMatrix, const glm::mat4 identity_matrix, const glm::mat4 projection_matrix, const glm::vec3 position) const
{
	unsigned int projectionLoc = glGetUniformLocation(shaderProg, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection_matrix));

	// Set view matrix (constant during the draw)
	unsigned int viewLoc = glGetUniformLocation(shaderProg, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Calculate transformation matrix by combining translation, scale, and rotation
	glm::mat4 transformation_matrix = TranslationMatrix(identity_matrix, position) * ScaleMatrix(identity_matrix) * RotationMatrix(identity_matrix);

	// Set transformation matrix (changes during the draw)
	unsigned int transformLoc = glGetUniformLocation(shaderProg, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformation_matrix));

	// Draw
	glUseProgram(shaderProg);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, mesh_indices.size(), GL_UNSIGNED_INT, 0);
}

void Model3D::drawWithTexture(GLuint shaderProg, GLuint VAO, std::vector<unsigned int> mesh_indices, const glm::mat4 viewMatrix, const glm::mat4 identity_matrix, const glm::mat4 projection_matrix, const glm::vec3 position) const
{

	unsigned int projectionLoc = glGetUniformLocation(shaderProg, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection_matrix));

	// Set view matrix (constant during the draw)
	unsigned int viewLoc = glGetUniformLocation(shaderProg, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	// Calculate transformation matrix by combining translation, scale, and rotation
	glm::mat4 transformation_matrix = TranslationMatrix(identity_matrix, position) * ScaleMatrix(identity_matrix) * RotationMatrix(identity_matrix);

	// Set transformation matrix (changes during the draw)
	unsigned int transformLoc = glGetUniformLocation(shaderProg, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformation_matrix));

	GLuint tex0Address = glGetUniformLocation(shaderProg, "tex0");
	glBindTexture(GL_TEXTURE_2D, tex0Address);
}

// Function to add a new model at a specific position
void Model3D::addModel(const glm::vec3& position)
{
	this->positions.push_back(position);
}

// Function to get the positions of all models
const std::vector<glm::vec3>& Model3D::getPositions() const
{
	return positions;
}




