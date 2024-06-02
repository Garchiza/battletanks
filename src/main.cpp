#include <glad/glad.h>                                                                  //Библиотека GLAD
#include <GLFW/glfw3.h>                                                                 //Библиотека GLFW
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
    if (!glfwInit()) {                                                                  //Если не получилось инициализировать glfw, программа закрывает с ошибкой
        std::cout << "!!!GLFW initalisation error!!!";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);					                    //Префикс версии OpenGL которую мы будем использовать (4.6);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);					                    //Постфикс версии OpenGL которую мы будем использовать (4.6). Таким образом можно уверить себя в том, что ты можешь использовать весь функционал версии 4.6

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);                      //Какая-та залупа, но нужная


    GLFWwindow* pWindow = glfwCreateWindow(WindowSizeX, WindowSizeY, "Battle tanks", NULL, NULL);	    //Создать окно. Ширина 640, высота 480, имя в ковычках, полноэкранный режим: NULL, ещё какой-то режим: NULL

    if (!pWindow) {									                                    //Проверка, создано ли окно или нет. (На этот раз с ошибкой!)
        std::cout << "!!!window creation error!!!";
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(pWindow, WndwSizeCallback);
    glfwSetKeyCallback(pWindow, KeyCallback);

    glfwMakeContextCurrent(pWindow);					                    	        //Указатель, с каким окном ведётся работа


    if (!gladLoadGL()) {							                                    //Инициализация OpenGL GLAD с ошибкой
        std::cout << "!!!GLAD initialisation error!!!";
        return -1;
    }


    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;		            //Вывести название видеокарты
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;	        //Вывести версию OpenGL


    glClearColor(1, 1, 0, 1);							                                //Назначить цвет окна

    while (!glfwWindowShouldClose(pWindow)) {				                    	    //Цикл отрисовки окна, который продолжается до тех пор, пока пользователь это окно не закроет.
        glClear(GL_COLOR_BUFFER_BIT);						                            //Очищает буфер цвета
        glfwSwapBuffers(pWindow);							                            //Меняет местами задний и передний буфер цвета (чаго). Ну короче буфера нужны чтобы помочь с проблемой разрывов кадров. Эта система называется double buffering
        glfwPollEvents();								                                //Позволяет glfw работать с приходящими от пользователя ивентами
    }


    glfwTerminate();			                                                        //В коем-то веке закрыть программу
    return 0;
}