file(GLOB_RECURSE WalnutApp_SRC LIST_DIRECTORIES false src/*.cpp)

add_executable(WalnutApp ${WalnutApp_SRC})
target_include_directories(WalnutApp PRIVATE src)

install(WalnutApp DESTINATION bin)