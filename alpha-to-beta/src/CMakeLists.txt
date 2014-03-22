include_directories(
	# Current DIR
	.;
	# EntityX
	${ALPHA_TO_BETA_SOURCE_DIR}/dependencies/entityx;
	# Core LIB
	${ALPHA_TO_BETA_SOURCE_DIR}/core/src;
	# SFML
	${SFML_SOURCE_DIR};
)

link_directories(
	#Link TinyXML
	${ALPHA_TO_BETA_BINARY_DIR}/dependencies/tinyxml2;
	# EntityX
	${ALPHA_TO_BETA_BINARY_DIR}/dependencies/entityx;
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

	tinyxml2static;		# XML Lib
	entityx;			# ES Lib 
	core; 				# Core Lib
	sfml-system; 		# SFML core
	sfml-window;		# SFML Window system
	sfml-graphics;		# SFML Graphics system
)

