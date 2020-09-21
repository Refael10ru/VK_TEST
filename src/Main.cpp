
#define DEBUG 0
//#define GLFW_INCLUDE_VULKAN
#include "Window.hpp"

#include "VK_Instance.hpp"
#include "VK_Device.hpp"
//#include <vulkan/vulkan.h>
#include <iostream>
#include <vector>
#include <cstring>

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr) {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    } else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
        func(instance, debugMessenger, pAllocator);
    }
}


int main(int argc , char* argv[])
{   
int tmp = okek::Window::initWindow();

assert(tmp != GLFW_NO_ERROR);

if(glfwVulkanSupported() == GLFW_TRUE)
{
    std::cout << "we found a loader!\n";
}
else
{
    std::cout << "no loader :(\n";
    glfwTerminate();
    return 0;
}


okek::Window MainWindow = okek::Window(std::string("VK_test"), std::string(argv[0]));

#ifdef DEBUG
VkDebugUtilsMessengerEXT debugMessenger;
okek::VK_Instance::debug = true;
#else
okek::VK_Instance::debug = false;
#endif


VkApplicationInfo appInfo{};
appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
appInfo.pApplicationName = "Hello Triangle";
appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
appInfo.pEngineName = "No Engine";
appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
appInfo.apiVersion = VK_API_VERSION_1_0;


VkInstanceCreateInfo createInfo{};
createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
createInfo.pApplicationInfo = &appInfo;

uint32_t glfwExtensionCount = 0;
const char** glfwExtensions;
std::vector<char*> ExtensionNames;
std::vector<char*> LayerNames;
ExtensionNames.resize(glfwExtensionCount);
memcpy(ExtensionNames.data(),glfwGetRequiredInstanceExtensions(&glfwExtensionCount)
,glfwExtensionCount*sizeof(char*));
if(!okek::VK_Instance::checkLayerSupport(&LayerNames))
{
    std::cout << "Missing layers!" << std::endl;
}
if(!okek::VK_Instance::checkExtensionSupport(&ExtensionNames))
{
    std::cout << "Missing extensions!" << std::endl;
}
createInfo.enabledLayerCount = static_cast<uint32_t>(LayerNames.size());
createInfo.ppEnabledLayerNames = LayerNames.data();
createInfo.enabledExtensionCount = static_cast<uint32_t>(ExtensionNames.size());
createInfo.ppEnabledExtensionNames = ExtensionNames.data();



VkDebugUtilsMessengerCreateInfoEXT CreateDebugInfo{};
CreateDebugInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
CreateDebugInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
CreateDebugInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
CreateDebugInfo.pfnUserCallback = okek::VK_Instance::debugCallback;
CreateDebugInfo.pUserData = nullptr; // Optional

createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &CreateDebugInfo;

okek::VK_Instance instance(&createInfo);

if (CreateDebugUtilsMessengerEXT(instance.GetInstance(), &CreateDebugInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
    throw std::runtime_error("failed to set up debug messenger!");
}


std::vector<VkPhysicalDevice> devices;
okek::VK_PhDevice::GetPhisicalDevices(&devices , instance.GetInstance());

std::cout << devices.size();
int FoundDevice = -1;
for(int i = 0; i < devices.size(); i++)
{
    std::cout << devices[i];
 if(okek::VK_PhDevice::isDeviceSuitable(&devices[i]) != -1)
 {
    
    FoundDevice = i;
    break;

 }

}
if(FoundDevice == -1)
 throw(std::runtime_error("failed to choose a proper device"));

okek::VK_PhDevice Phdevice(devices[FoundDevice]);

okek::VK_Device device(&instance , &Phdevice);


while(!glfwWindowShouldClose(MainWindow.GetWindow()))
{

    MainWindow.InputHandle();
    glfwPollEvents();
}

if (okek::VK_Instance::debug) 
{
    DestroyDebugUtilsMessengerEXT(instance.GetInstance(), debugMessenger, nullptr);
}

glfwTerminate();
return 0;
}