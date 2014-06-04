# We need version 2.8
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# Project name, used later
project(ALPHA_TO_BETA)
	
option("CMAKE_BUILD_TYPE" "Project build type" "Release")

# Set module path for extra find modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/Modules/")

# Find SFML before proceeding
find_package(SFML COMPONENTS system window graphics REQUIRED)
# Math library
find_package(GLM REQUIRED)
# ZLib compression
find_package(ZLIB REQUIRED)

# Boost vars
if(${WIN32})
    # Only link statically for windows
    set(Boost_USE_STATIC_LIBS ON)
    set(Boost_USE_MULTITHREADED ON)
    set(Boost_USE_STATIC_RUNTIME ON)
endif(${WIN32})
# Find boost
find_package(Boost COMPONENTS system filesystem REQUIRED)
# Lua 5.2
find_package(Lua52 REQUIRED)
# Luabind library
find_package(Luabind REQUIRED)

# C++11 support and warnings 
if(${UNIX})
    add_definitions(-Wall)
    # C++ specific compiler options
    list(APPEND CMAKE_CXX_FLAGS "-std=c++11")
elseif(${WIN32})
	# Wall is too much
	add_definitions(/W3)
endif(${UNIX})

# Conditional compilation 
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	MESSAGE(STATUS "Building in debug mode...")
	# Debug mode
    add_definitions(-D_DEBUG)
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
	MESSAGE(STATUS "Building in release mode...")
	# Release mode
    #add_definitions(-DNDEBUG -O3)
endif(${CMAKE_BUILD_TYPE} STREQUAL "Debug")

# Set executable output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Add tinyxml2 dependency
message(STATUS "Configuring TinyXML2...")
add_subdirectory("dependencies/tinyxml2")

message(STATUS "Configuring tmx-parser...")
add_subdirectory("dependencies/tmx-parser")

message(STATUS "Configuring FastDelegate")
add_subdirectory("dependencies/FastDelegate")

#Add artemis dependency
message(STATUS "Configuring Artemis-Cpp...")
add_subdirectory("dependencies/Artemis-Cpp")

message(STATUS "Configuring Box2D...")
add_subdirectory("dependencies/Box2D")

# Core framework
message(STATUS "Configuring Core...")
add_subdirectory("core/src")
# Game
message(STATUS "Configuring Game...")
add_subdirectory("alpha-to-beta/src")

# Copy game assets
#file(COPY ${CMAKE_SOURCE_DIR}/alpha-to-beta/assets DESTINATION ${ALPHA_TO_BETA_BINARY_DIR})

#install(TARGETS ALPHA_TO_BETA DESTINATION alphatobeta)

include(CPack)
