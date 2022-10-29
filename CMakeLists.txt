cmake_minimum_required (VERSION 3.13)

project(Walnut)

set(CMAKE_PREFIX_PATH ${Vulkan_DIR})
find_package(Vulkan REQUIRED)

# TODO: Figure out how to allow later standards
if(NOT DEFINED CMAKE_CXX_STANDARD)
	set(CMAKE_CXX_STANDARD 17)
endif()

add_subdirectory(vendor)
add_subdirectory(Walnut)
add_subdirectory(WalnutApp)
