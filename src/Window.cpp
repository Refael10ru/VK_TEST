
#include "Window.hpp"

namespace okek
{
Window::Window(std::string name, std::string pathtobin, Camera* Player,int width,
int height, int mousesensitivity, float fov)
{   
    this->name = name;
    this->FOV = fov;
    this->MouseSensitivity = mousesensitivity;
    this->Width = width;
    this->Height = height;
    this->player = Player;
    this->MouseX = width/2;
    this->MouseY = height/2;
    if(player != nullptr)
    {
    this->player->constrainPitch = true;
    }
    for(int i = pathtobin.length()-1 ; i >= 0; i--)
        if(*(&pathtobin[i]) == '/')
        {
        pathtobin.resize(i+1);
        break;
        }
    this->PathToBin = pathtobin;


    this->window = glfwCreateWindow(Width, Height, name.c_str(), NULL, NULL);
    if (!window) {
    fprintf(stderr, "ERROR: could not open window with GLFW3\n");
    glfwTerminate();

    }
    
    glfwSetWindowUserPointer(this->window, this);


    glfwSetScrollCallback(this->window, Window::scroll_callback);
    glfwSetCursorPosCallback(this->window, Window::mouse_callback);  
    glfwSetFramebufferSizeCallback(this->window, Window::FrameBufferSizeCallBack);
    glfwMakeContextCurrent(this->window);

    /*
    // get version info
    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION); // version as a string
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);*/
}
Window::~Window()
{
    glfwDestroyWindow(this->window);
    
}

void Window::InputHandle()
{ 
this->deltatime = glfwGetTime() - this->lastframe;
this->lastframe = glfwGetTime();
float cameraSpeed = 4.5f * this->deltatime;
if(player != nullptr)
{
if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    this->player->position += cameraSpeed * glm::normalize(player->Front);
if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    player->position -= cameraSpeed * glm::normalize(player->Front);
if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    player->position -= glm::normalize(glm::cross(player->Front, player->Up)) * cameraSpeed;
if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    player->position += glm::normalize(glm::cross(player->Front, player->Up)) * cameraSpeed;



if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    player->position -= player->Up* cameraSpeed;

if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    player->position += player->Up* cameraSpeed;
    //resrt...

    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
    
        player->position = glm::vec3(0,0,4);
        player->Yaw = 0;
        player->Pitch = 0;
    }
    
    
    player->updateCameraVectors();
    }
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Window::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{ reinterpret_cast<Window*>(glfwGetWindowUserPointer(window))->ProcessMouseMovement(xpos,ypos);}
void Window::ProcessMouseMovement(float xpos, float ypos)
    {
        
        float xoffset = xpos - this->MouseX;
        float yoffset = ypos - this->MouseY;
        this->MouseY = ypos;
        this->MouseX = xpos;

        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;
        if(player != nullptr)
        {
            player->Yaw   += xoffset;
            player->Pitch -= yoffset;
        

            // make sure that when pitch is out of bounds, screen doesn't get flipped
            if (this->player->constrainPitch)
            {
                if (player->Pitch > 890.0f)
                    player->Pitch = 890.0f;
                if (player->Pitch < -890.0f)
                    player->Pitch = -890.0f;
            }
            

            // update Front, Right and Up Vectors using the updated Euler angles
            player->updateCameraVectors();
        }
    }
void Window::FrameBufferSizeCallBack(GLFWwindow* window, int width, int height)
{ reinterpret_cast<Window*>(glfwGetWindowUserPointer(window))->SizeChanged(window,width,height); }
void Window::SizeChanged(GLFWwindow* window, int width, int height)
{   }
void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{ reinterpret_cast<Window*>(glfwGetWindowUserPointer(window))->scroll(xoffset,yoffset);}
void Window::scroll(double xoffset, double yoffset)
{
    FOV -= (float)yoffset;
    if (FOV < 1.0f)
        FOV = 1.0f;
    if (FOV > 75.0f)
        FOV = 75.0f; 
}
int Window::initWindow() 
{
    int tmp = glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    return tmp;
}

void Window::GetWindowsSurface(VkSurfaceKHR* surface)
{
    #if (defined (_WIN32) || defined (_WIN64))

        std::cout << "I'm on Windows!" << std::endl;

    #elif (defined (LINUX) || defined (__linux__))
    
        std::cout << "I'm on Linux!" << std::endl;

    #endif
}

};