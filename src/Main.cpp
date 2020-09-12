
#include "Window.h"
#include <iostream>


int main(int argc , char* argv[])
{
    glfwInit();

    glfwVulkanSupported();

    okek::Window MainWindow = okek::Window(std::string(argv[0]));


    while(!glfwWindowShouldClose(MainWindow.GetWindow()))
    {

    glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}