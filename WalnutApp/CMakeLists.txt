file(GLOB_RECURSE WalnutApp_SRC LIST_DIRECTORIES false src/*.cpp)

add_executable(WalnutApp ${WalnutApp_SRC})
target_include_directories(WalnutApp PRIVATE src)
target_link_libraries(WalnutApp PRIVATE Walnut)

# setup internal project compile definition
if(WIN32)
    target_compile_definitions(Walnut PRIVATE WL_PLATFORM_WINDOWS)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(WalnutApp PRIVATE WL_DEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    target_compile_definitions(WalnutApp PRIVATE WL_RELEASE)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(WalnutApp PRIVATE WL_DIST)
endif()

install(TARGETS WalnutApp DESTINATION bin)
