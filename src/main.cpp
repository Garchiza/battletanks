#include <glad/glad.h>                                                                  //���������� GLAD
#include <GLFW/glfw3.h>                                                                 //���������� GLFW
#include <iostream>

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

int main(void)
{
    if (!glfwInit()) {                                                                  //���� �� ���������� ���������������� glfw, ��������� ��������� � �������
        std::cout << "!!!GLFW initalisation error!!!";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);					                    //������� ������ OpenGL ������� �� ����� ������������ (4.6);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);					                    //�������� ������ OpenGL ������� �� ����� ������������ (4.6). ����� ������� ����� ������� ���� � ���, ��� �� ������ ������������ ���� ���������� ������ 4.6

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);                      //�����-�� ������, �� ������


    GLFWwindow* pWindow = glfwCreateWindow(WindowSizeX, WindowSizeY, "Battle tanks", NULL, NULL);	    //������� ����. ������ 640, ������ 480, ��� � ��������, ������������� �����: NULL, ��� �����-�� �����: NULL

    if (!pWindow) {									                                    //��������, ������� �� ���� ��� ���. (�� ���� ��� � �������!)
        std::cout << "!!!window creation error!!!";
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(pWindow, WndwSizeCallback);
    glfwSetKeyCallback(pWindow, KeyCallback);

    glfwMakeContextCurrent(pWindow);					                    	        //���������, � ����� ����� ������ ������


    if (!gladLoadGL()) {							                                    //������������� OpenGL GLAD � �������
        std::cout << "!!!GLAD initialisation error!!!";
        return -1;
    }


    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;		            //������� �������� ����������
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;	        //������� ������ OpenGL


    glClearColor(1, 1, 0, 1);							                                //��������� ���� ����

    while (!glfwWindowShouldClose(pWindow)) {				                    	    //���� ��������� ����, ������� ������������ �� ��� ���, ���� ������������ ��� ���� �� �������.
        glClear(GL_COLOR_BUFFER_BIT);						                            //������� ����� �����
        glfwSwapBuffers(pWindow);							                            //������ ������� ������ � �������� ����� ����� (����). �� ������ ������ ����� ����� ������ � ��������� �������� ������. ��� ������� ���������� double buffering
        glfwPollEvents();								                                //��������� glfw �������� � ����������� �� ������������ ��������
    }


    glfwTerminate();			                                                        //� ����-�� ���� ������� ���������
    return 0;
}