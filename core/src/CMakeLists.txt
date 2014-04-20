include_directories(
	# Subdirectory include
	.;
	# TinyXML include
	${ALPHA_TO_BETA_SOURCE_DIR}/dependencies/tinyxml2;
	# TMX Parser
	${tmxparser_SOURCE_DIR};
	# Artemis
	${ALPHA_TO_BETA_SOURCE_DIR}/dependencies/Artemis-Cpp/include;
	# Boost library
	${Boost_INCLUDE_DIR};
)

link_directories(
	# Artemis-Cpp
	${ALPHA_TO_BETA_BINARY_DIR}/dependencies/Artemis-Cpp;
    # TinyXML
    ${tinyxml2_BINARY_DIR}
	# TMX Parser
#	${ALPHA_TO_BETA_BINARY_DIR}/dependencies/tmx-parser;
    ${tmxparser_BINARY_DIR}
)

set(
	MAIN_SRC
	"Game.cpp"
	"Game.h"
	"SFMLPtrDef.h"
)

set(
	COMPONENTS_SRC
	"Components/ParsedComponent.h"
	"Components/Renderable.cpp"
	"Components/Renderable.h"
	"Components/Transform.cpp"
	"Components/Transform.h"
	"Components/Physics.cpp"
	"Components/Physics.h"
)

set(
	ENTITIES_SRC
	"Entities/EntityFactory.cpp"
	"Entities/EntityFactory.h"
	"Entities/Level.cpp"
	"Entities/Level.h"
)

# Graphics/*.{h|cpp}
set(
	GRAPHICS_SRC
	"Graphics/Camera2D.cpp"
	"Graphics/Camera2D.h"
	"Graphics/SpriteBatch.cpp"
	"Graphics/SpriteBatch.h"
	"Graphics/TextureRegion.cpp"
	"Graphics/TextureRegion.h"
)

set(
	MAPS_SRC
	"Maps/MapLoader.cpp"
	"Maps/MapLoader.h"
)

set(
	RESOURCES_SRC
	"Resources/GenericObjectFactory.h"
	"Resources/Locator.h"
	"Resources/ResourceHolder.h"
	"Resources/ResourceDef.h"
	"Resources/SharedResourceHolder.h"
	"Resources/SingletonResourceHolder.h"
	"Resources/XMLoader.cpp"
	"Resources/XMLoader.h"
)

set(
	SCREENS_SRC
	"Screens/IScreen.h"
	"Screens/ScreenManager.cpp"
	"Screens/ScreenManager.h"
)

set(
	SYSTEMS_SRC
	"Systems/MovementSystem.cpp"
	"Systems/MovementSystem.h"
	"Systems/RenderSystem.cpp"
	"Systems/RenderSystem.h"
	"Systems/WorldManager.cpp"
	"Systems/WorldManager.h"
)

set(
	UTILS_SRC
	"Utils/FileSystem.cpp"
	"Utils/FileSystem.h"
	"Utils/Logger.cpp"
	"Utils/Logger.h"
	"Utils/String.cpp"
	"Utils/String.h"
	"Utils/QuadTree.h"
)

# Add all current *.cpp files in to build
set(
	SOURCE_FILE_LIST;

	${MAIN_SRC};
	${COMPONENTS_SRC};
	${ENTITIES_SRC};
	${GRAPHICS_SRC};
	${MAPS_SRC};
	${RESOURCES_SRC};
	${SCREENS_SRC};
	${SYSTEMS_SRC};
	${UTILS_SRC};
)

# Create library
add_library(
	core 				# Name
	STATIC 				# Dynamic library build
  	${SOURCE_FILE_LIST}	# List of files
)


# Link static libraries
target_link_libraries(
	core; 

    ${Boost_LIBRARIES};
	ArtemisCpp; 	# Artemis EC System
	tinyxml2static; # TinyXML
    tmxparser;		# TMX parser
)
