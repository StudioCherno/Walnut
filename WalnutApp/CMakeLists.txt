file(GLOB_RECURSE WalnutApp_SRC LIST_DIRECTORIES false src/*.cpp)

add_executable(WalnutApp ${WalnutApp_SRC})
target_include_directories(WalnutApp PRIVATE src)
target_link_libraries(WalnutApp PRIVATE Walnut)

install(TARGETS WalnutApp DESTINATION bin)
