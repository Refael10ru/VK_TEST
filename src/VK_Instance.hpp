
#ifndef _VK_INSTANCE_
#define _VK_INSTANCE_ 
#include "../extern/Vulkan/include/vulkan/vulkan.h"

#include <vector>

namespace okek
{
class VK_Instance
{
public:
    friend class VK_PhDevice;
    friend class VK_Device;
    VK_Instance(VkInstanceCreateInfo *createInfo);
    ~VK_Instance();

    static bool checkLayerSupport(std::vector<char*>* LayerNames);
    static bool checkExtensionSupport(std::vector<char*> *ExtensionNames);
    static bool checkLayerSupport(std::vector<VkLayerProperties> *layernames);
    static bool checkExtensionSupport(std::vector<VkExtensionProperties> *ExtensionNames);
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData);

    inline VkInstance GetInstance(){ return this->instance; }

    bool debuged;
    inline static bool debug = false;
protected:
    VkInstance instance;
    std::vector<char*> extensions;
    std::vector<char*> layers;
    //std::vector<void(*)(VkInstance instance)> subs;
};
};
#endif