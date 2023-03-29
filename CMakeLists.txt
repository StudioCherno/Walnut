cmake_minimum_required (VERSION 3.13)

project(Walnut)
set(VULKAN_SDK "${PROJECT_SOURCE_DIR}/vendor/VulkanSDK-Headers-And-Libs/VulkanSDK")
set(Vulkan_INCLUDE_DIR "${VULKAN_SDK}/Include/")
set(Vulkan_LIBRARY "${VULKAN_SDK}/Lib/vulkan-1.lib")
find_package(Vulkan REQUIRED)

if(NOT DEFINED CMAKE_CXX_STANDARD)
	set(CMAKE_CXX_STANDARD 17)
endif()

add_subdirectory(vendor)
add_subdirectory(Walnut)
add_subdirectory(WalnutApp)
