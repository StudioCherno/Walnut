file(GLOB_RECURSE Walnut_SRC LIST_DIRECTORIES false src/*.cpp)

add_library(Walnut STATIC ${Walnut_SRC})
target_include_directories(Walnut PUBLIC src)
# set_property(TARGET Walnut PROPERTY POSITION_INDEPENDENT_CODE ON)

# setup internal project compile definition
if(WIN32)
    target_compile_definitions(Walnut PRIVATE WL_PLATFORM_WINDOWS)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(Walnut PRIVATE WL_DEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    target_compile_definitions(Walnut PRIVATE WL_RELEASE)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(Walnut PRIVATE WL_DIST)
endif()

target_link_libraries(Walnut PUBLIC imgui glfw glm::glm stb_image Vulkan::Vulkan)
if(WIN32)
    target_link_libraries(Walnut PUBLIC dwmapi)
endif()

install(TARGETS Walnut DESTINATION bin)
