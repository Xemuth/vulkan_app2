#include "vkContext.h"
#include "windowApp.h"

#include <glfw/glfw3.h>

namespace vkapp
{

std::vector<const char*> get_glfw_vk_required_extension()
{
    uint32_t     glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char*> vec;
    for (int i = 0; i < glfwExtensionCount; i++)
        vec.push_back(glfwExtensions[i]);

    return vec;
}

Error WindowApp::Run(VkContext& context)
{
    for (;;)
    {
        switch (_status)
        {
        case WindowStatus::INIT:
            // create_glfw_window();
            break;
        }
    }
}

}   // namespace vkapp