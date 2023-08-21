#ifndef VK_CONTEXT_HEADER
#define VK_CONTEXT_HEADER
#include "definition.h"

#include <vulkan/vulkan.h>

namespace vkapp
{

struct VkContext
{
    VkInstance               _instance;
    VkPhysicalDevice         _physical_device;
    VkDebugUtilsMessengerEXT _debugMessenger;
    std::vector<const char*> _vk_extensions_names;
    std::vector<const char*> _vk_layers_names;

    Error init();
    Error clear(Error last_error);
};

}   // namespace vkapp

#endif