cmake_minimum_required(VERSION 3.22.1)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message("Setting build type to 'Debug' as none was specified.")
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif()

message("Build type is : ${CMAKE_BUILD_TYPE}")

project(spicy-pierogi VERSION 1.0 LANGUAGES CXX)
set(CONFIG_PATH ${CMAKE_CURRENT_SOURCE_DIR}/config)
set(RESOURCES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/resources)
set(SHADERS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/shaders)

find_package(jsoncpp REQUIRED)
find_package(log4cplus REQUIRED)
find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cc)
target_link_libraries(${PROJECT_NAME} PRIVATE jsoncpp_lib log4cplus::log4cplus Vulkan::Vulkan glfw glm::glm)
target_compile_definitions(${PROJECT_NAME} PUBLIC CONFIG_PATH=\"${CONFIG_PATH}/\")