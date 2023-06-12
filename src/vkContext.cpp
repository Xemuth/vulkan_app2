#include "vkContext.h"

#include <vulkan/vulkan.h>

namespace vkapp
{

void create_vk_instance(VkContext& context)
{
    VkApplicationInfo info;
    info.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    info.pApplicationName   = "vulkan_app_2";
    info.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
    info.pEngineName        = "";
    info.engineVersion      = VK_MAKE_VERSION(0, 0, 0);
    info.apiVersion         = VK_API_VERSION_1_3;

    VkInstanceCreateInfo instance;
    instance.sType            = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instance.pApplicationInfo = &info;
    // instance.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
    instance.pNext = nullptr;
}

}   // namespace vkapp