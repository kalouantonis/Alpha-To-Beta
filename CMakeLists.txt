# We need version 2.8
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# Project name, used later
project(ALPHA_TO_BETA)
	
# Find SFML before proceeding
find_package(SFML REQUIRED)
find_package(Boost REQUIRED)

# C++11 support and warnings 
add_definitions(-std=c++11 -Wall)

# Conditional compilation 
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	MESSAGE(STATUS "Building in debug mode...")
	# Debug mode
	add_definitions(-D_DEBUG -ggdb)
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
	MESSAGE(STATUS "Building in release mode...")
	# Release mode
	add_definitions(-DNDEBUG -O3)
endif(${CMAKE_BUILD_TYPE} STREQUAL "Debug")

# Set executable output directory
# TODO: Change to INSTALL script
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Add tinyxml2 dependency
message(STATUS "Configuring TinyXML2...")
add_subdirectory("dependencies/tinyxml2")

#Add entityx dependency
#message(STATUS "Configuring EntityX...")
#add_subdirectory("dependencies/entityx")

#Add entityx dependency
message(STATUS "Configuring Artemis-Cpp...")
add_subdirectory("dependencies/Artemis-Cpp")

# Core framework
message(STATUS "Configuring Core...")
add_subdirectory("core/src")
# Game
message(STATUS "Configuring Game...")
add_subdirectory("alpha-to-beta/src")

# Copy game assets
file(COPY ${CMAKE_SOURCE_DIR}/alpha-to-beta/assets DESTINATION ${CMAKE_BINARY_DIR})