#include "definition.h"
#include "vkContext.h"
#include "windowApp.h"

#include <iostream>
#include <vulkan/vulkan.h>

#define LOGGER_NAME "main"
// static auto logger = std::make_shared<spdlog::logger>(spdlog::get("master_logger")->clone());

int main()
{
    vkapp::VkContext context;

    context._vk_extensions_names = std::move(vkapp::get_glfw_vk_required_extension());
    context._vk_layers_names     = std::move(std::vector<const char*>{});

    vkapp::WindowApp window;
    auto             err = window.run(context);
    if (err != vkapp::Error::NO_ERROR)
    {
        std::cout << "Error occured: " << vkapp::ErrorStr[err] << std::endl;
    }
    return 0;
}