#ifndef DEFINITION_HEADER
#define DEFINITION_HEADER
#include <cstdint>
#include <vector>

namespace vkapp
{

enum Error : uint32_t
{
    NO_ERROR,
};

const char* const ErrorStr[] = {"no error", "Dummy error"};

}   // namespace vkapp

#endif