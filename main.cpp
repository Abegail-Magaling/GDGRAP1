#include "Models/Model3D.h"
#include "Models/Light//DirectionalLight.h"

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

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


//Modifier for the model's x Position
float theta = 0.0f; // Initialize rotation angle to 0

// Set rotation axis to x-axis initially
float axis_x = 0.0f;
float axis_y = 1.0f;
float axis_z = 0.0f;

// Adjust initial position and scale of the model
float x_mod = 0.0f;
float y_mod = -20.0f;
float z_mod = -50.0f;

float scale_x = 0.5f;
float scale_y = 0.5f;
float scale_z = 0.5f;


void Key_Callback(GLFWwindow* window // Pointer to window
    , int key// keycode of press
    , int scancode // physical postion of the press
    , int action // either press / release
    , int mods) // which modifier keys are held down
{
    //translation
    if (key == GLFW_KEY_D)
    {
        axis_y = 1.0f;
        axis_x = 0.0f;
        theta += 5.0f;
    }
    if (key == GLFW_KEY_A)
    {
        axis_y = -1.0f;
        axis_x = 0.0f;
        theta += 5.0f;
    }
    if (key == GLFW_KEY_W)
    {
        axis_y = 0.0f;
        axis_x = 1.0f;
        theta += 5.0f;
    }

    if (key == GLFW_KEY_S)
    {
        axis_y = 0.0f;
        axis_x = -1.0f;
        theta += 5.0f;
    }

    //scale
    if (key == GLFW_KEY_Q)
    {
        axis_z = 1.0f;
        axis_x = 0.0f;
        axis_x = 0.0f;
        theta += 5.0f;;
    }
    if (key == GLFW_KEY_E)
    {
        axis_z = -1.0f;
        axis_x = 0.0f;
        axis_x = 0.0f;
        theta += 5.0f;;
    }


    //rotation
    //if (key == GLFW_KEY_UP)
    //{
    //    brightness += 1;
    //    lightVar.setBrightness(brightness);
    //}
    //if (key == GLFW_KEY_DOWN)
    //{
    //    brightness += -1;
    //    lightVar.setBrightness(brightness);
    //}
    //if (key == GLFW_KEY_LEFT) {
    //    //lightColor *= 1.1f;
    //    lightVar.setAmbientStr(-0.2);
    //}
    //if (key == GLFW_KEY_RIGHT) {
    //    //lightColor *= 0.9f;
    //    lightVar.setAmbientStr(0.2);
    //}
    //projection
    if (key == GLFW_KEY_Z) {
        z_mod += 1.0f;
    }
    if (key == GLFW_KEY_X) {
        z_mod -= 1.0f;
    }
}

GLfloat lightSphereVertices[] =
{   //  COORDINATES //
    -0.1f, -0.1f,  0.1f,
    -0.1f, -0.1f, -0.1f,
     0.1f, -0.1f, -0.1f,
     0.1f, -0.1f,  0.1f,
    -0.1f,  0.1f,  0.1f,
    -0.1f,  0.1f, -0.1f,
     0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f,
};

GLuint lightSphereIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

int main(void)
{
    //load the vert shader file into a string stream
    std::fstream vertSrc("Shaders/sample.vert");
    std::stringstream vertBuff;

    //Add the file stream to the string stream
    vertBuff << vertSrc.rdbuf();

    //Convert the stream to a character array
    std::string vertS = vertBuff.str();
    const char* v = vertS.c_str();

    //load the frag shader file into a string stream
    std::fstream fragSrc("Shaders/sample.frag");
    std::stringstream fragBuff;

    //Add the file stream to the string stream
    fragBuff << fragSrc.rdbuf();

    //Convert the stream to a character array
    std::string fragS = fragBuff.str();
    const char* f = fragS.c_str();

    GLFWwindow* window;

    float window_width = 600;
    float window_height = 600;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(600, 600, "Abegail Laureen Magaling", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    gladLoadGL();

    int img_width, img_height, colorChannels;

    //Create a Vertex Shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    //Assign the source to the vertex shader
    glShaderSource(vertexShader, 1, &v, NULL);

    //Compile the vertex shader
    glCompileShader(vertexShader);

    //Create a Fragment Shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    //Assign the source to the fragment shader
    glShaderSource(fragmentShader, 1, &f, NULL);

    //Compile the fragment shader
    glCompileShader(fragmentShader);


    //Create shader program
    GLuint shaderProg = glCreateProgram();


    //Attach the compiled Vertex shader
    glAttachShader(shaderProg, vertexShader);
    //Attach the compiled Vertex shader
    glAttachShader(shaderProg, fragmentShader);

    //Finalize the compilation process
    glLinkProgram(shaderProg);

    //Set the callback function to the window
    glfwSetKeyCallback(window, Key_Callback);

    std::string path = "3D/mario.obj";
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> material;
    std::string warning, error;
    tinyobj::attrib_t attributes;
    bool success = tinyobj::LoadObj(&attributes, &shapes, &material, &warning, &error, path.c_str());
    std::vector<GLfloat> fullVertexData;
    for (int i = 0; i < shapes[0].mesh.indices.size(); i++) {
        //assign the index data for easy access
        tinyobj::index_t vData = shapes[0].mesh.indices[i];

        fullVertexData.push_back(
            attributes.vertices[(vData.vertex_index * 3)]
        );

        fullVertexData.push_back(
            attributes.vertices[(vData.vertex_index * 3) + 1]
        );

        fullVertexData.push_back(
            attributes.vertices[(vData.vertex_index * 3) + 2]
        );

        fullVertexData.push_back(
            attributes.normals[(vData.normal_index * 3)]
        );

        fullVertexData.push_back(
            attributes.normals[(vData.normal_index * 3) + 1]
        );

        fullVertexData.push_back(
            attributes.normals[(vData.normal_index * 3) + 2]
        );

        fullVertexData.push_back(
            attributes.texcoords[(vData.texcoord_index * 2)]
        );

        fullVertexData.push_back(
            attributes.texcoords[(vData.texcoord_index * 2) + 1]
        );
    }
    stbi_set_flip_vertically_on_load(true);

    unsigned char* tex_bytes = stbi_load("3D/Mario_Albedo.png", &img_width, &img_height, &colorChannels, 0);
    GLuint texture;
    glGenTextures(1, &texture); //generate reference
    glActiveTexture(GL_TEXTURE0); //set the current texture to texture 0
    glBindTexture(GL_TEXTURE_2D, texture);//bind
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_width, img_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex_bytes);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(tex_bytes);

    GLfloat vertices[]
    {
        //x  //y   //z
        0.f, 0.5f, 0.f, //0
        -0.5f, -0.5f, 0.f, //1
        0.5f, -0.5f, 0.f //2

    };

    GLuint indices[]
    {
        0,1,2
    };

    GLfloat UV[]{
        0.f, 1.f,
        0.f, 0.f,
        1.f, 1.f,
        1.f, 0.f,
        1.f, 1.f,
        1.f, 0.f,
        0.f, 1.f,
        0.f, 0.f
    };


    GLuint VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(GLfloat) * fullVertexData.size(),
        fullVertexData.data(),
        GL_DYNAMIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(0);

    GLintptr normalPtr = 3 * sizeof(float);

    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(float),
        (void*)normalPtr
    );

    glEnableVertexAttribArray(1);

    //since uv starts at index 3 or the 4th index of our vertex data
    GLintptr uvPtr = 6 * sizeof(float);

    glVertexAttribPointer(
        2,                      //index is 2 for texCoordinates
        2,                      //UV is 2 floats (U, V)
        GL_FLOAT,               //data type of array
        GL_FALSE,               //not normalized = GL_FALSE
        8 * sizeof(float),      //vertex has 5 floats in it
        (void*)uvPtr            //add in the offset in the end
    );

    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    glm::mat4 identity_martix = glm::mat4(1.0f);

    glm::mat4 identity_matrix = glm::mat4(1.0f);

    glm::mat4 projectionMatrix = glm::perspective(glm::radians(60.f), // FOV
        window_height / window_width, // Aspect Ratio
        0.1f, // ZNear > 0
        500.f); // ZFar

    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 20.0f);

    //glm::mat4 cameraPositionMatrix = glm::translate(glm::mat4(1.0f), cameraPos * -1.0f);

    glm::vec3 WorldUp = glm::vec3(0, 1.0f, 0);

    glm::vec3 Center = glm::vec3(0, 1.0f, 0);

    glm::mat4 viewMatrix = glm::lookAt(cameraPos, Center, WorldUp);

    glEnable(GL_DEPTH_TEST);


    Model3D model;
    Light lightInput;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Start with the translation matrix_mod
        glm::mat4 transformation_matrix = glm::translate(identity_martix, glm::vec3(x_mod, y_mod, z_mod));

        //Multiply the resulting matrix with the scale matrix
        transformation_matrix = glm::scale(transformation_matrix, glm::vec3(scale_x, scale_y, scale_z));

        //Finally, multiply it with the rotation matrix
        transformation_matrix = glm::rotate(transformation_matrix, glm::radians(theta), glm::normalize(glm::vec3(axis_x, axis_y, axis_z)));

        //Get location of projection matrix
        unsigned int projectionLoc = glGetUniformLocation(shaderProg, "projection");
        //Assign the matrix
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

        unsigned int viewLoc = glGetUniformLocation(shaderProg, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

        //Get location of transformation matrix
        unsigned int transformLoc = glGetUniformLocation(shaderProg, "transform");
        //Assign the matrix
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformation_matrix));


        GLuint tex0Address = glGetUniformLocation(shaderProg, "tex0");
        glBindTexture(GL_TEXTURE_2D, texture);

        GLuint cameraPosAdd = glGetUniformLocation(shaderProg, "cameraPos");
        glUniform3fv(cameraPosAdd, 1, glm::value_ptr(cameraPos));

        Light lightVar;
        DirectionalLight* addLight = new DirectionalLight(shaderProg);
        lightVar.lightInput(window);

        glUniform1i(tex0Address, 0);

        glUseProgram(shaderProg);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, fullVertexData.size() / 8);


        /*glUseProgram(shaderProg);
        glBindVertexArray(newVAO);
        glDrawElements(GL_TRIANGLES, newMeshIndices.size(), GL_UNSIGNED_INT, 0);*/

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
    //Cleanup
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}