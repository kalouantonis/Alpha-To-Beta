project(alphatobeta)

include_directories(
	# Current DIR
	.;
	# Artemis
	${ALPHA_TO_BETA_SOURCE_DIR}/dependencies/Artemis-Cpp/include;
	# TinyXML
	${ALPHA_TO_BETA_SOURCE_DIR}/dependencies/tinyxml2;
	# TMX Parser
	${ALPHA_TO_BETA_SOURCE_DIR}/dependencies/tmx-parser;
    # FastDelegate
    ${FastDelegate_SOURCE_DIR};
	# Box2D
	${Box2D_SOURCE_DIR};
	# Boost
	${Boost_INCLUDE_DIR};
	# Core LIB
	${ALPHA_TO_BETA_SOURCE_DIR}/core/src;
	# SFML
	${SFML_SOURCE_DIR};
)

link_directories(
	#Link TinyXML
	${ALPHA_TO_BETA_BINARY_DIR}/dependencies/tinyxml2;
	# Boost
	${Boost_LIBRARY_DIRS};
	# Core	
	${ALPHA_TO_BETA_BINARY_DIR}/core/src;
)

set(
    EVENTS_SRC
    "Events/JumpEvent.cpp"
    "Events/JumpEvent.h"
    "Events/JumpListener.cpp"
    "Events/JumpListener.h"
)

set(
	MAIN_SRC
	"main.cpp"
)

# Screens/*.{h|cpp}
set(
	SCREENS_SRC
	"Screens/GameScreen.cpp"
	"Screens/GameScreen.h"
)

set(
	SYSTEMS_SRC
	"Systems/PlayerInputSystem.cpp"
	"Systems/PlayerInputSystem.h"
)

set(
	SOURCE_FILE_LIST;

    ${EVENTS_SRC};
	${MAIN_SRC};
	${SCREENS_SRC};
	${SYSTEMS_SRC};
)

# Create executable
add_executable(alphatobeta ${SOURCE_FILE_LIST})

set(
	LIBRARIES;
	
	#${Boost_LIBRARIES};
	core; # Core library
	${SFML_LIBRARIES}; # SFML
)


# Link dependant libraries
target_link_libraries(
    alphatobeta;

	#${Boost_LIBRARIES};     # Only used components that were requested
	${LIBRARIES}
)

install(TARGETS alphatobeta DESTINATION alphatobeta)
