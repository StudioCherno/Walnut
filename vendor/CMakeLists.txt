# Setup vendor libraries
## IMGUI (No CMake support, we have to roll or own)
set(imgui_SRC imgui/imgui.cpp imgui/imgui_draw.cpp imgui/imgui_tables.cpp imgui/imgui_widgets.cpp imgui/imgui_demo.cpp)
add_library(imgui STATIC ${imgui_SRC})
target_include_directories(imgui PUBLIC imgui)
set_property(TARGET imgui PROPERTY POSITION_INDEPENDENT_CODE ON)

## GLFW (comes with its own CMakeLists, let's use that)
add_subdirectory(GLFW)

## glm (comes with its own CMakeLists, let's use that)
add_subdirectory(glm)

## stb_image (header-only, create a dummy interface library)
add_library(stb_image INTERFACE)
target_include_directories(stb_image INTERFACE stb_image)
