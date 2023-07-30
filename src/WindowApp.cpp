#include "windowApp.h"
#include "vkContext.h"

#include <glfw/glfw3.h>

namespace
{
}   // namespace

namespace vkapp
{

struct WindowApp::Impl
{
    WindowApp*  _parent;
    GLFWwindow* _window;

    Error initGLFW();
    Error runGLFW();
    Error endGLFW();
};

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

Error WindowApp::Impl::initGLFW()
{
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    _window = glfwCreateWindow(800, 600, "Vulkan", nullptr, nullptr);

    return Error::NO_ERROR;
}

Error WindowApp::Impl::runGLFW()
{
    while (!glfwWindowShouldClose(_window))
    {
        if (_parent->last_error() != Error::NO_ERROR)
        {
            glfwSetWindowShouldClose(_window, 1);
            return Error::SHOULD_CLOSE;
        }
        glfwPollEvents();
    }
    return Error::NO_ERROR;
}

Error WindowApp::Impl::endGLFW()
{
    glfwDestroyWindow(_window);
    glfwTerminate();
    return Error::NO_ERROR;
}

Error WindowApp::run(VkContext& context)
{
    for (;;)
    {
        auto status = Error::NO_ERROR;
        switch (_status)
        {
        case WindowStatus::INIT:
            status = pImpl->initGLFW();
            if (status != Error::NO_ERROR)
                _errors.push(status);
            _status = WindowStatus::RUN;
            break;
        case WindowStatus::RUN:
            status = pImpl->runGLFW();
            if (status != Error::NO_ERROR)
                _status = WindowStatus::END;
        case WindowStatus::END:
            status = pImpl->runGLFW();
            if (status != Error::NO_ERROR)
                _errors.push(status);
            break;
        }
        if (_status == WindowStatus::END)
            break;
    }
    return last_error();
}

Error WindowApp::last_error()
{
    if (_errors.size() == 0)
        return Error::NO_ERROR;
    return _errors.top();
}

WindowApp::WindowApp()
{
    pImpl          = std::make_shared<Impl>();
    pImpl->_parent = this;
}

}   // namespace vkapp