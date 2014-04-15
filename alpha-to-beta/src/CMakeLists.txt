include_directories(
	# Current DIR
	.;
	# Artemis
	${ALPHA_TO_BETA_SOURCE_DIR}/dependencies/Artemis-Cpp/include;
	# TinyXML
	${ALPHA_TO_BETA_SOURCE_DIR}/dependencies/tinyxml2;
	# TMX Parser
	${ALPHA_TO_BETA_SOURCE_DIR}/dependencies/tmx-parser;
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
	"Systems/GameManager.cpp"
	"Systems/GameManager.h"
)

set(
	SOURCE_FILE_LIST;
	${MAIN_SRC};
	${SCREENS_SRC};
	${SYSTEMS_SRC};
)

# Create executable
add_executable(alphatobeta ${SOURCE_FILE_LIST})

# Link dependant libraries
target_link_libraries(
	alphatobeta;

    ${Boost_SYSTEM_LIBRARY};
    ${Boost_FILESYSTEM_LIBRARY};
    core; 							# Core Lib
	${SFML_LIBRARIES};
)

