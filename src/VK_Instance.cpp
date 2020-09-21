#include "VK_Instance.hpp"

#include <exception> 
#include <iostream>
#include <cstring>

namespace okek
{

VK_Instance::VK_Instance(VkInstanceCreateInfo *createInfo)
{

this->extensions.resize(createInfo->enabledExtensionCount);
memcpy(this->extensions.data(),createInfo->ppEnabledExtensionNames,sizeof(char*)*createInfo->enabledExtensionCount);
this->layers.resize(createInfo->enabledLayerCount);
memcpy(this->layers.data(),createInfo->ppEnabledLayerNames,sizeof(char*)*createInfo->enabledLayerCount);
if(okek::VK_Instance::debug)
{
this->extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
this->layers.push_back("VK_LAYER_KHRONOS_validation");
createInfo->enabledLayerCount = static_cast<uint32_t>(this->layers.size());
createInfo->ppEnabledLayerNames = this->layers.data();
createInfo->enabledExtensionCount = static_cast<uint32_t>(this->extensions.size());
createInfo->ppEnabledExtensionNames = this->extensions.data();
if(!okek::VK_Instance::checkLayerSupport(&(this->layers)))
{
    std::cout << "Missing layers!" << std::endl;
}
if(!okek::VK_Instance::checkExtensionSupport(&(this->extensions)))
{
    std::cout << "Missing extensions!" << std::endl;
}
}
if (vkCreateInstance(createInfo, nullptr, &this->instance) != VK_SUCCESS) 
{
    throw std::runtime_error("failed to create instance!");
}
this->debuged = okek::VK_Instance::debug;
}

VK_Instance::~VK_Instance()
{
    vkDestroyInstance(this->instance,nullptr);
    
}

bool VK_Instance::checkLayerSupport(std::vector<char*>* LayerNames) {
    uint32_t LayerCount;
    vkEnumerateInstanceLayerProperties(&LayerCount, nullptr);
    
    std::vector<VkLayerProperties> availableLayer(LayerCount);
    vkEnumerateInstanceLayerProperties(&LayerCount, availableLayer.data());

    int cleared = 0;
    for (int iterator = 0; iterator < LayerNames->size(); iterator++) {
        bool layerFound = false;

        for (const auto& LayerProperties : availableLayer) {
            if (strcmp(LayerNames->operator[](iterator), LayerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }

        if (!layerFound) cleared++;
        if(cleared != 0)
        {
            LayerNames->operator[](iterator-cleared) = LayerNames->operator[](iterator);
        }
    }
    
    if(cleared == 0) return true;
    LayerNames->resize(LayerNames->size()-cleared);
    return false;
}
bool VK_Instance::checkExtensionSupport(std::vector<char*>* ExtensionNames)
{
    uint32_t ExtensionCount;
    vkEnumerateInstanceExtensionProperties(nullptr, &ExtensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtension(ExtensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &ExtensionCount, availableExtension.data());

    int cleared = 0;
    for (int iterator = 0; iterator < ExtensionNames->size(); iterator++) {
        bool layerFound = false;

        for (const auto& ExtensionProperties : availableExtension) {
            if (strcmp(ExtensionNames->operator[](iterator), ExtensionProperties.extensionName) == 0) {
                layerFound = true;
                break;
            }
        }
        
        if(!layerFound) cleared++;
        if(cleared != 0)
        {
            ExtensionNames->operator[](iterator-cleared) = ExtensionNames->operator[](iterator);
        }
    }
    
    if(cleared == 0) return true;
    ExtensionNames->resize(ExtensionNames->size()-cleared);
    return false;
}
bool VK_Instance::checkLayerSupport(std::vector<VkLayerProperties> *Layers)
{
    uint32_t LayerCount;
    vkEnumerateInstanceLayerProperties(&LayerCount, nullptr);
    
    std::vector<VkLayerProperties> availableLayer(LayerCount);
    vkEnumerateInstanceLayerProperties(&LayerCount, availableLayer.data());

    int cleared = 0;
    for (int iterator = 0; iterator < Layers->size(); iterator++) {
        bool layerFound = false;

        for (const auto& LayerProperties : availableLayer) {
            if (strcmp(Layers->operator[](iterator).layerName , LayerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }

        if (!layerFound) cleared++;
        if(cleared != 0)
        {
            Layers->operator[](iterator-cleared) = Layers->operator[](iterator);
        }
    }
    
    if(cleared == 0) return true;
    Layers->resize(Layers->size()-cleared);
    return false;
}
bool VK_Instance::checkExtensionSupport(std::vector<VkExtensionProperties> *Extensions)
{
    uint32_t ExtensionCount;
    vkEnumerateInstanceExtensionProperties(nullptr, &ExtensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtension(ExtensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &ExtensionCount, availableExtension.data());

    int cleared = 0;
    for (int iterator = 0; iterator < Extensions->size(); iterator++) {
        bool layerFound = false;

        for (const auto& ExtensionProperties : availableExtension) {
            if (strcmp(Extensions->operator[](iterator).extensionName, ExtensionProperties.extensionName) == 0) {
                layerFound = true;
                break;
            }
        }
        
        if(!layerFound) cleared++;
        if(cleared != 0)
        {   

            Extensions->operator[](iterator-cleared) = Extensions->operator[](iterator);
        }
    }
    if(cleared == 0) return true;
    Extensions->resize(Extensions->size()-cleared);
    return false;
}
VKAPI_ATTR VkBool32 VKAPI_CALL VK_Instance::debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData) {
    if(messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
        std::cerr << "validation layer: " << pCallbackData->pMessage  << std::endl;

    return VK_FALSE;
}

};