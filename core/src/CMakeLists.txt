include_directories(
	# Subdirectory include
	.;
	# TinyXML include
	${ALPHA_TO_BETA_SOURCE_DIR}/dependencies/tinyxml2;
	# Artemis
	${ALPHA_TO_BETA_SOURCE_DIR}/dependencies/Artemis-Cpp/include;
	# Boost library
	${Boost_INCLUDE_DIR};
)


link_directories(
	# Artemis-Cpp
	${ALPHA_TO_BETA_BINARY_DIR}/dependencies/Artemis-Cpp;
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
	# "Entities/EntityFactory.cpp"
	# "Entities/EntityFactory.h"
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
	RESOURCES_SRC
	"Resources/GenericObjectFactory.h"
	"Resources/ResourceHolder.h"
	"Resources/ResourceHolderDef.h"
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
	"Utils/Logger.cpp"
	"Utils/Logger.h"
	"Utils/QuadTree.h"
)

# Add all current *.cpp files in to build
set(
	SOURCE_FILE_LIST;

	${MAIN_SRC};
	${COMPONENTS_SRC};
	${ENTITIES_SRC};
	${GRAPHICS_SRC};
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


# Link libraries
target_link_libraries(
	core; 

	ArtemisCpp; 	# Artemis EC System
)