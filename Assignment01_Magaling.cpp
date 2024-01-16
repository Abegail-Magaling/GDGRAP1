#include <GLFW/glfw3.h>
#include <cmath>
#define PI 3.14159265359

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(480, 480, "Abegail Laureen Magaling", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        float vertices[5][2];
        float radius = 0.5;

        glBegin(GL_POLYGON);

        for (int i = 0; i < 5; ++i) {
            float theta = (i * 2 * PI) / 5;
            vertices[i][0] = radius * cos(theta);
            vertices[i][1] = radius * sin(theta);
            glVertex2f(vertices[i][0], vertices[i][1]);
        }

        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}