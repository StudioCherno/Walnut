cmake_minimum_required (VERSION 3.16.0)
set(CMAKE_CXX_STANDARD 17)
message(STATUS "CMAKE_CXX_STANDARD " + ${CMAKE_CXX_STANDARD})

set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "CMAKE_CXX_STANDARD_REQUIRED " + ${CMAKE_CXX_STANDARD_REQUIRED})
set(CXX_EXTENSIONS OFF)
message(STATUS "CXX_EXTENSIONS " + ${CXX_EXTENSIONS})

project (Walnut)

message(STATUS "CMAKE_SYSTEM " + ${CMAKE_SYSTEM})
message(STATUS "CMAKE_SYSTEM_NAME " + ${CMAKE_SYSTEM_NAME})
#set(CMAKE_SYSTEM_VERSION latest)
#message(STATUS "CMAKE_SYSTEM_VERSION " + ${CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION})
message(STATUS "CMAKE_SYSTEM_VERSION " + ${CMAKE_SYSTEM_VERSION})
message(STATUS "CMAKE_SYSTEM_PROCESSOR " + ${CMAKE_SYSTEM_PROCESSOR})

message(STATUS "CMAKE_HOST_SYSTEM" + ${CMAKE_HOST_SYSTEM})

message(STATUS "CMAKE_CXX_COMPILER " + ${CMAKE_CXX_COMPILER})
message(STATUS "CMAKE_CXX_COMPILER_ID " + ${CMAKE_CXX_COMPILER_ID})
message(STATUS "CMAKE_CXX_COMPILER_VERSION " + ${CMAKE_CXX_COMPILER_VERSION})
message(STATUS "CMAKE_CXX_COMPILER_LOADED " + ${CMAKE_CXX_COMPILER_LOADED})

if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "Setting build type to 'Debug' as none was specified.")
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
else()
    message("-- CMAKE_BUILD_TYPE=" "${CMAKE_BUILD_TYPE}")
endif()

message(STATUS "CMake Source Dir " + ${CMAKE_SOURCE_DIR})
message(STATUS "CMake Binary Dir " + ${CMAKE_BINARY_DIR})

set(CONAN_DISABLE_CHECK_COMPILER On)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

#### Third Party Libs which are not already built ####
add_library(third-party 
                Walnut/src/Walnut/ImGui/ImGuiBuild.cpp)

#### ENGINE ###
add_library (walnut
                Walnut/src/Walnut/Application.cpp
                Walnut/src/Walnut/Image.cpp
                Walnut/src/Walnut/Random.cpp
            )

target_include_directories(walnut PRIVATE ${CONAN_INCLUDE_DIRS})
#target_compile_definitions(walnut PUBLIC VK_USE_PLATFORM_MACOS_MVK)
target_link_libraries(walnut PRIVATE third-party ${CONAN_LIBS})
                        # MoltenVK 
                        # glfw3 
                        # /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/System/Library/Frameworks/Cocoa.framework
                        # /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/System/Library/Frameworks/IOKit.framework
                        # )

add_custom_command(TARGET walnut POST_BUILD
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/post-build.sh
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Running post build script..."
)

ADD_CUSTOM_COMMAND(TARGET walnut POST_BUILD
                     COMMAND ln -s ${CONAN_LIB_DIRS_MOLTENVK}/libMoltenVK.dylib bin/libMoltenVK.dylib
                     WORKING_DIRECTORY ${CMAKE_BINARY_DIR} 
                     COMMENT "Generating symbolic link for libMoltenVK!!!")

ADD_CUSTOM_COMMAND(TARGET walnut POST_BUILD
                     COMMAND ln -s ${CONAN_LIB_DIRS_MOLTENVK}/libMoltenVK.dylib bin/libvulkan.1.dylib
                     WORKING_DIRECTORY ${CMAKE_BINARY_DIR} 
                     COMMENT "Generating symbolic link for libMoltenVK!!!")

add_subdirectory(WalnutApp)
