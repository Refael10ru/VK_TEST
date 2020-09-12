
#include "Window.h"


int main(int argc , char* argv[])
{
    glfwInit();
    okek::Window MainWindow = okek::Window(std::string(argv[0]));

    while(!glfwWindowShouldClose(MainWindow.GetWindow()))
    {

    glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}