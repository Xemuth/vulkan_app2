#ifndef DEFINITION_HEADER
#define DEFINITION_HEADER
#include <cstdint>
#include <vector>

#include <vulkan/vk_enum_string_helper.h>

namespace vkapp
{

typedef uint32_t AppError;

enum Error : uint32_t
{
    NO_ERROR,
    SHOULD_CLOSE,
};

const char* const ErrorStr[] = {"no error", "Error occured and window must close"};

static const char* error_to_string(AppError error)
{
    return string_VkResult(static_cast<VkResult>(error));
}

}   // namespace vkapp

#endif