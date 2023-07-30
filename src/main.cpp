#include "vkContext.h"
#include "windowApp.h"

#include <iostream>

int main()
{
    vkapp::VkContext context;

    context._vk_extensions_names = std::move(vkapp::get_glfw_vk_required_extension());

    vkapp::WindowApp window;
    auto             err = window.run(context);
    if (err != vkapp::Error::NO_ERROR)
    {
        std::cout << "Error occured: " << vkapp::ErrorStr[err] << std::endl;
    }
    return 0;
}