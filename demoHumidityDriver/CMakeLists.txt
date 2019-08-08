cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME_LOCAL demoHumidityDriver)

#Find source files
file(GLOB_RECURSE SRC ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)

#Target
add_executable(${PROJECT_NAME_LOCAL} ${SRC})

#Include header files
target_include_directories(${PROJECT_NAME_LOCAL} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)

#Dependencies
target_link_libraries(${PROJECT_NAME_LOCAL} Adapters)
target_link_libraries(${PROJECT_NAME_LOCAL} Humidity)
target_link_libraries(${PROJECT_NAME_LOCAL} RasPiDrivers)

