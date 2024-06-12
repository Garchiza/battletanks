#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Renderer/ShaderProgramm.h"
#include "Resources/ResourceManager.h"

GLfloat point[] = {
    0.0f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f
};
GLfloat color[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};

int WindowSizeX = 640, WindowSizeY = 480;

void KeyCallback(GLFWwindow* pWindow, int key, int scncd, int act, int mode) {
    if (key == GLFW_KEY_ESCAPE && act == GLFW_PRESS){
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
}

void WndwSizeCallback(GLFWwindow* pWindow, int x, int y) {
    WindowSizeX = x;
    WindowSizeY = y;
    glViewport(0,0, WindowSizeX, WindowSizeY);
}

int main(int argc, char** argv) {
    if (!glfwInit()) {
        std::cout << "!!!GLFW initalisation error!!!";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* pWindow = glfwCreateWindow(WindowSizeX, WindowSizeY, "Battle tanks", NULL, NULL);

    if (!pWindow) {
        std::cout << "!!!window creation error!!!";
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(pWindow, WndwSizeCallback);
    glfwSetKeyCallback(pWindow, KeyCallback);

    glfwMakeContextCurrent(pWindow);


    if (!gladLoadGL()) {
        std::cout << "!!!GLAD initialisation error!!!";
        return -1;
    }


    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    glClearColor(1, 1, 0, 1);

    {
        ResourceManager resourceManager(argv[0]);
        auto pDefaultShaderProgram = resourceManager.loadShaders("DefaulShader", "res/shaders/vertex.txt", "res/shaders/fragment.txt");
        if (!pDefaultShaderProgram) {
            std::cout << "Can not create shader programm: " << "Default Shader" << std::endl;
            return -1;
        }

        GLuint points_vbo = 0;
        glGenBuffers(1, &points_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

        GLuint colors_vbo = 0;
        glGenBuffers(1, &colors_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);

        GLuint vao = 0;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);


        while (!glfwWindowShouldClose(pWindow)) {
            glClear(GL_COLOR_BUFFER_BIT);
            pDefaultShaderProgram->use();
            glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glfwSwapBuffers(pWindow);
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}