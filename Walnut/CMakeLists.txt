file(GLOB_RECURSE Walnut_SRC LIST_DIRECTORIES false src/*.cpp)

add_library(Walnut STATIC ${Walnut_SRC})
target_include_directories(Walnut PUBLIC src)
set_property(TARGET Walnut PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries(Walnut PUBLIC imgui glfw glm::glm stb_image vulkan)

install(TARGETS Walnut DESTINATION bin)
