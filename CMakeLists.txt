cmake_minimum_required (VERSION 3.13)

project(Walnut)

if(NOT DEFINED Vulkan_DIR)
	message(ERROR "Please provide a valid path to the VulkanSDK")
endif()

set(CMAKE_PREFIX_PATH ${Vulkan_DIR})
find_package(Vulkan REQUIRED)

# TODO: Figure out how to allow later standards
set(CMAKE_CXX_STANDARD 17)

# add_subdirectory(Walnut)
add_subdirectory(WalnutApp)
