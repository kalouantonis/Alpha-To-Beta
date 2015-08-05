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
    # LuaPlus
    ${ALPHA_TO_BETA_SOURCE_DIR}/dependencies/luaplus;
	# Core LIB
	${ALPHA_TO_BETA_SOURCE_DIR}/core/src;
	# SFML
	${SFML_SOURCE_DIR};
)

link_directories(
	#Link TinyXML
	${ALPHA_TO_BETA_BINARY_DIR}/dependencies/tinyxml2;
    # Luabind
    ${LUABIND_LIBRARY_DIR};
	# Core	
	${ALPHA_TO_BETA_BINARY_DIR}/core/src;
)

set(
    COMPONENTS_SRC
    "Components/JumpBehaviour.cpp"
    "Components/JumpBehaviour.h"
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
    "Screens/GameManager.cpp"
    "Screens/GameManager.h"
)

set(
	SYSTEMS_SRC
	"Systems/PlayerInputSystem.cpp"
	"Systems/PlayerInputSystem.h"
)

set(
	SOURCE_FILE_LIST;

    ${COMPONENTS_SRC};
    ${EVENTS_SRC};
	${MAIN_SRC};
	${SCREENS_SRC};
	${SYSTEMS_SRC};
)

# Create executable
add_executable(alphatobeta ${SOURCE_FILE_LIST})

# Link dependant libraries
target_link_libraries(
    alphatobeta;

	core; # Core library
	${SFML_LIBRARIES}; # SFML
	${LUA_LIBRARIES};
	${LUABIND_LIBRARIES};
)

install(TARGETS alphatobeta DESTINATION alphatobeta)
