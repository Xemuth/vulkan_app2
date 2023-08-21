#include "vkContext.h"
#include "definition.h"

#include <spdlog/spdlog.h>
#include <vulkan/vulkan.h>

#define LOGGER_NAME "VkContext"
#if defined(ENABLE_LOG)
static auto logger = MasterLogger::get_logger(LOGGER_NAME);
#define LOGGER(action) logger->action
#else
#define LOGGER(action)
#endif

namespace
{

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
{
    LOGGER(debug("validation layer:" + std::string(pCallbackData->pMessage)));
    return VK_FALSE;
}

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger)
{
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr)
    {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    }
    else
    {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator)
{
    LOGGER(debug("Destroying debug callback"));
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr)
    {
        func(instance, debugMessenger, pAllocator);
    }
}

VkResult check_validation_layer_support(vkapp::VkContext& context)
{
    std::find(context._vk_layers_names.begin(), context._vk_layers_names.end(), VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    bool layer_found = false;
    for (const char* layer : context._vk_layers_names)
    {
        layer_found = false;
        for (const auto& available_layer : availableLayers)
        {

            if (strcmp(layer, available_layer.layerName) == 0)
            {
                layer_found = true;
                break;
            }
        }
        if (!layer_found)
            return VkResult::VK_ERROR_LAYER_NOT_PRESENT;
    }
    return VkResult::VK_SUCCESS;
}

VkResult create_vk_instance(vkapp::VkContext& context)
{
    VkApplicationInfo info;
    info.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    info.pApplicationName   = "vulkan_app_2";
    info.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
    info.pEngineName        = "";
    info.engineVersion      = VK_MAKE_VERSION(0, 0, 0);
    info.apiVersion         = VK_API_VERSION_1_3;

    VkInstanceCreateInfo instance;
    instance.sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instance.pApplicationInfo        = &info;
    instance.enabledExtensionCount   = context._vk_extensions_names.size();
    instance.ppEnabledExtensionNames = context._vk_extensions_names.data();
#ifdef ENABLE_VALIDATION_LAYER
    auto result = check_validation_layer_support(context);
    if (result != VkResult::VK_SUCCESS)
        return result;
    instance.enabledLayerCount   = context._vk_layers_names.size();
    instance.ppEnabledLayerNames = context._vk_layers_names.data();
#else
    instance.enabledLayerCount   = 0;
    instance.ppEnabledLayerNames = nullptr;
#endif
    // instance.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
    instance.pNext = nullptr;
    return vkCreateInstance(&instance, nullptr, &context._instance);
}

VkResult setupDebugMessenger(vkapp::VkContext& context)
{
    VkDebugUtilsMessengerCreateInfoEXT createInfo;
    createInfo.sType           = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType     = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = debugCallback;
    return CreateDebugUtilsMessengerEXT(context._instance, &createInfo, nullptr, &context._debugMessenger);
}

}   // namespace

namespace vkapp
{

Error VkContext::init()
{
    auto result = create_vk_instance(*this);
    if (result != VkResult::VK_SUCCESS)
        return Error::VULKAN_INIT_ERROR;
#ifdef ENABLE_VALIDATION_LAYER
    result = setupDebugMessenger(*this);
    if (result != VkResult::VK_SUCCESS)
        return Error::VULKAN_INIT_ERROR;
#endif
    return Error::NO_ERROR;
}

Error VkContext::clear(Error last_error)
{
}

}   // namespace vkapp