#ifndef _WINDOW_
#define _WINDOW_

#include "../extern/Vulkan/include/vulkan/vulkan.h"
#include "../extern/glfw/include/GLFW/glfw3.h" // GLFW helper library
#include <string>
#include "Camera.hpp"

namespace okek
{
    class Window
    {
friend class GLFWwindow;
public:
    Window(std::string name = "oke!", std::string PathToBin = std::string(), Camera* Player = nullptr ,int width = 680,
    int height = 480, int mousesensitivity = 1.0f, float fov = 65.0f);

    ~Window();

    void InputHandle();

    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    void mouseInput(double xpos, double ypos);

    static void FrameBufferSizeCallBack(GLFWwindow* window, int width, int height);
    void SizeChanged(GLFWwindow* window, int width, int height);

    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    void scroll(double xoffset, double yoffset);


    void ProcessMouseMovement(float xoffset, float yoffset);

    void GetWindowsSurface(VkSurfaceKHR* surface);

    inline GLFWwindow* GetWindow() { return window; }
    inline std::string GetPath() { return PathToBin; }

    static int initWindow();
protected:

    GLFWwindow* window;

    Camera* player;

    float Width;
    float Height;

    float deltatime;
    double lastframe;

    float FOV;
    float MouseY;
    float MouseX;
    float MouseSensitivity;
    bool first;

    std::string name;
    std::string PathToBin;
    };
};


#endif