#include "VK_Instance.hpp"
#include <optional>
#include <vector>

namespace okek 
{

class VK_PhDevice
{
public:
    friend class VK_Device;
    VK_PhDevice(VkPhysicalDevice physicalDevice, std::vector<VkQueueFamilyProperties>* Families = nullptr);

    static void GetPhisicalDevices(std::vector<VkPhysicalDevice>* devices, VkInstance instance);
    static bool isDeviceSuitable(VkPhysicalDevice* device);
    static void findQueueFamilies(VkPhysicalDevice device, std::vector<VkQueueFamilyProperties>* Families);
    static int findSutableQueue(VkPhysicalDevice* device, uint32_t req);

    inline VkPhysicalDevice GetDevice(){ return this->physicalDevice; }
protected:
    VkPhysicalDevice physicalDevice;
    std::vector<VkQueueFamilyProperties> QueueFamilies;

};

class VK_Device
{
public:
    VK_Device(VK_Instance* pInstance, VK_PhDevice* pPhDevice);
    ~VK_Device();

protected:
    VkDevice device;
    VkQueue queue;
    
};

}