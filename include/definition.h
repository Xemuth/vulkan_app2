#ifndef DEFINITION_HEADER
#define DEFINITION_HEADER
#include <cstdint>
#include <vector>

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <vulkan/vk_enum_string_helper.h>

#define ENABLE_LOG
#if defined(ENABLE_LOG)
struct MasterLogger
{
    static auto get_logger(const char* logger_name)
    {
        static std::shared_ptr<spdlog::logger> master_logger = nullptr;
        if (!master_logger)
        {
            std::vector<spdlog::sink_ptr> log_output;
            log_output.push_back(std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>());
            log_output.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("vulkan_app2.txt"));
            master_logger = std::make_shared<spdlog::logger>("master_logger", begin(log_output), end(log_output));
            master_logger->set_level(spdlog::level::debug);
        }
        return master_logger->clone(logger_name);
    }
};
#endif

namespace vkapp
{
typedef uint32_t AppError;

enum Error : uint32_t
{
    NO_ERROR,
    GLFW_FAILED_TO_INIT,
    SHOULD_CLOSE,
    VULKAN_INIT_ERROR,
};

const char* const ErrorStr[] = {"no error", "GLFW failed to initialise", "Error occured and window must close", "Vulkan failed to initialise"};

static const char* error_to_string(AppError error)
{
    return string_VkResult(static_cast<VkResult>(error));
}

}   // namespace vkapp

#endif