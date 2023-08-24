
#ifndef WINDOW_APP_HEADER
#define WINDOW_APP_HEADER

#include "definition.h"

#include <memory>
#include <stack>

typedef struct GLFWwindow GLFWwindow;

namespace vkapp
{

struct VkContext;

std::vector<const char*> get_glfw_vk_required_extension();

enum class WindowStatus
{
    INIT,
    RUN,
    END,
};

struct WindowApp
{
    WindowApp();
    ~WindowApp() = default;

    WindowApp(const WindowApp&) = delete;
    WindowApp(WindowApp&&)      = delete;

    WindowApp& operator=(const WindowApp&) = delete;
    WindowApp& operator=(WindowApp&&)      = delete;

    Error run(VkContext&);
    Error last_error();

    WindowStatus      _status = WindowStatus::INIT;
    std::stack<Error> _errors;

    struct Impl;
    std::shared_ptr<Impl> pImpl;
};

}   // namespace vkapp

#endif