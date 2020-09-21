
#include "VK_Device.hpp"
#include <iostream>

namespace okek
{
void VK_PhDevice::GetPhisicalDevices(std::vector<VkPhysicalDevice>* devices,VkInstance instance)
{
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
    if (deviceCount == 0) {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }
    devices->resize(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices->data());
}
bool VK_PhDevice::isDeviceSuitable(VkPhysicalDevice* device) 
{
    VkPhysicalDeviceProperties deviceProperties;
    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceProperties(*device, &deviceProperties);
    vkGetPhysicalDeviceFeatures(*device, &deviceFeatures);


    std::cout << " cheking device: " << deviceProperties.deviceName << "\n";

    if(okek::VK_PhDevice::findSutableQueue(device , VK_QUEUE_GRAPHICS_BIT) == -1) return false;

    if((deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && 
    deviceFeatures.geometryShader));
    {   
        return true;
        
    }
    return false;

}
int VK_PhDevice::findSutableQueue(VkPhysicalDevice* device, uint32_t req)
{
    std::vector<VkQueueFamilyProperties> Families(0);
    okek::VK_PhDevice::findQueueFamilies(*device, &Families);

    for(int i = 0; i < Families.size(); i++)
    {
        if(Families[i].queueFlags & req)
        { 
            return i;
        }
    }
    return -1;
}
void VK_PhDevice::findQueueFamilies(VkPhysicalDevice device, std::vector<VkQueueFamilyProperties>* Families)
{
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
    Families->resize(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, Families->data());
}
VK_PhDevice::VK_PhDevice(VkPhysicalDevice physicalDevice, std::vector<VkQueueFamilyProperties>* pFamilies)
{
    this->physicalDevice = physicalDevice;

    if(pFamilies != nullptr)
        this->QueueFamilies = *pFamilies;
    else
        okek::VK_PhDevice::findQueueFamilies(physicalDevice , &this->QueueFamilies);
}

// --------------- Device ----------------->

VK_Device::VK_Device(VK_Instance* pInstance, VK_PhDevice* pPhDevice)
{
    
VkDeviceQueueCreateInfo queueCreateInfo{};
queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
queueCreateInfo.queueFamilyIndex = okek::VK_PhDevice::findSutableQueue(&pPhDevice->physicalDevice , VK_QUEUE_GRAPHICS_BIT);
//queueCreateInfo.queueFamilyIndex = 0;
queueCreateInfo.queueCount = 1;

float queuePriority = 1.0f;
queueCreateInfo.pQueuePriorities = &queuePriority;

VkPhysicalDeviceFeatures deviceFeatures{};

VkDeviceCreateInfo createInfo{};
createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

createInfo.pQueueCreateInfos = &queueCreateInfo;
createInfo.queueCreateInfoCount = 1;

createInfo.pEnabledFeatures = &deviceFeatures;

createInfo.enabledExtensionCount = 0;

if (pInstance->debuged) {
    createInfo.enabledLayerCount = static_cast<uint32_t>(pInstance->layers.size());
    createInfo.ppEnabledLayerNames = pInstance->layers.data();
} else {
    createInfo.enabledLayerCount = 0;
}

if (vkCreateDevice((pPhDevice->physicalDevice), &createInfo, nullptr, &this->device) != VK_SUCCESS) {
    throw std::runtime_error("failed to create logical device!");
}

VkQueue queues;

vkGetDeviceQueue(this->device, 0 , 0, &queues);

}

VK_Device::~VK_Device()
{
    vkDestroyDevice(this->device, nullptr);
}
}
    