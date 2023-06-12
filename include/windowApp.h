
#ifndef WINDOW_APP_HEADER
#define WINDOW_APP_HEADER

#include "definition.h"

typedef struct GLFWwindow GLFWwindow;

namespace vkapp
{

std::vector<const char*> get_glfw_vk_required_extension();

enum class WindowStatus
{
    INIT
};

struct WindowApp
{
    Error Run(VkContext&);

    GLFWwindow*  _window;
    WindowStatus _status;
};

}   // namespace vkapp

#endif