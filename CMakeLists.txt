cmake_minimum_required(VERSION 3.5)

project(RasPiCode LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 11)

#SubModule Directories
add_subdirectory(libGeminiDrivers/libInterfaces)
add_subdirectory(libGeminiDrivers/libHumidity)

#Project Directories
add_subdirectory(libAdapters)
add_subdirectory(libRasPiDrivers)
add_subdirectory(demoHumidityDriver)