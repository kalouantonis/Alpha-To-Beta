# We need version 2.8
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# Project name, used later
project(ALPHA_TO_BETA)
	
option("CMAKE_BUILD_TYPE" "Project build type" "Release")

# Set module path for extra find modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/Modules/")

# Find SFML before proceeding
find_package(SFML COMPONENTS system window graphics REQUIRED)
find_package(Luabind REQUIRED)

# Boost vars
if(${WIN32})
    # Only link statically for windows
    set(Boost_USE_STATIC_LIBS ON)
    set(Boost_USE_MULTITHREADED ON)
    set(Boost_USE_STATIC_RUNTIME ON)
endif(${WIN32})

find_package(Boost COMPONENTS system filesystem REQUIRED)

# C++11 support and warnings 
if(${UNIX})
	add_definitions(-std=c++11 -Wall)
elseif(${WIN32})
	# Wall is too much
	add_definitions(/W3)
endif(${UNIX})

# Conditional compilation 
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	MESSAGE(STATUS "Building in debug mode...")
	# Debug mode
    add_definitions(-D_DEBUG)
	
	if(${UNIX})
          #add_definitions(-ggdb)
	elseif(${WIN32})
		add_definitions(/g3)
	endif(${UNIX})
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
	MESSAGE(STATUS "Building in release mode...")
	# Release mode
    #add_definitions(-DNDEBUG -O3)
endif(${CMAKE_BUILD_TYPE} STREQUAL "Debug")

# Set executable output directory
# TODO: Change to INSTALL script
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
