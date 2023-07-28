#include "vkContext.h"
#include "windowApp.h"

#include <glfw/glfw3.h>

namespace
{
}   // namespace

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
            glfwInit();

            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
            glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

            _window = glfwCreateWindow(800, 600, "Vulkan", nullptr, nullptr);
            _status = WindowStatus::RUN;
            break;
        case WindowStatus::RUN:
            while (!glfwWindowShouldClose(_window))
            {
                glfwPollEvents();
            }
            _status = WindowStatus::END;
        case WindowStatus::END:
            break;
        }
    }
}

}   // namespace vkapp