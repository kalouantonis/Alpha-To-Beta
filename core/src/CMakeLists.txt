project(core)

include_directories(
    # Subdirectory include
    .;
    # TinyXML include
    ${ALPHA_TO_BETA_SOURCE_DIR}/dependencies/tinyxml2;
    # TMX Parser
    ${tmxparser_SOURCE_DIR};
    # FastDelegate
    ${FastDelegate_SOURCE_DIR};
    # Artemis
    ${ALPHA_TO_BETA_SOURCE_DIR}/dependencies/Artemis-Cpp/include;
    # Box2D
    ${Box2D_SOURCE_DIR};
    # Luaplus
    ${ALPHA_TO_BETA_SOURCE_DIR}/dependencies/luaplus;
    # Boost library
    ${Boost_INCLUDE_DIR};
)

link_directories(
	# Artemis-Cpp
	${ALPHA_TO_BETA_BINARY_DIR}/dependencies/Artemis-Cpp;
    # TinyXML
    ${tinyxml2_BINARY_DIR};
    # Box2D
    ${Box2D_BINARY_DIR};
	# TMX Parser
    ${tmxparser_BINARY_DIR};
    ${luaplus_BINARY_DIR};
)

set(
	MAIN_SRC
	"Game.cpp"
	"Game.h"
    "BaseGameManager.cpp"
    "BaseGameManager.h"
	"SFMLPtrDef.h"
)

set(
	COMPONENTS_SRC
	"Components/BaseAnimation.cpp"
	"Components/BaseAnimation.h"
    "Components/BaseScriptComponent.cpp"
    "Components/BaseScriptComponent.h"
	"Components/ParsedComponent.h"
    "Components/CameraFollower.cpp"
    "Components/CameraFollower.h"
	"Components/IRenderable.h"
    "Components/Renderable.cpp"
	"Components/Renderable.h"
	"Components/Transform.cpp"
	"Components/Transform.h"
	"Components/Physics.cpp"
	"Components/Physics.h"
	"Components/DynamicBody.cpp"
	"Components/DynamicBody.h"
	"Components/StaticBody.cpp"
	"Components/StaticBody.h"
    #"Components/JumpBehaviour.cpp"
    #"Components/JumpBehaviour.h"
	"Components/PlayerInput.cpp"
	"Components/PlayerInput.h"
)

set(
	DATA_STRUCTURES_SRC
#     "DataStructures/QuadTree.cpp"
#     "DataStructures/QuadTree.h"
#    "DataStructures/ConcurrentQueue.cpp"
    "DataStructures/ConcurrentQueue.h"
)

set(
    ENTITIES_SRC
    "Entities/EntityFactory.cpp"
    "Entities/EntityFactory.h"
    "Entities/Level.cpp"
    "Entities/Level.h"
    "Entities/Utils.cpp"
    "Entities/Utils.h"
    "Entities/WorldLocator.h"
)

set(
    EVENTS_SRC
    "Events/EventData.h"
    "Events/EventManager.cpp"
    "Events/EventManager.h"
    "Events/EventManagerImpl.cpp"
    "Events/EventManagerImpl.h"
    "Events/CollisionEvents.cpp"
    "Events/CollisionEvents.h"
)

# Graphics/*.{h|cpp}
set(
	GRAPHICS_SRC
	"Graphics/Animation.cpp"
	"Graphics/Animation.h"
	"Graphics/Camera2D.cpp"
	"Graphics/Camera2D.h"
	"Graphics/SpriteBatch.cpp"
	"Graphics/SpriteBatch.h"
	"Graphics/TextureRegion.cpp"
	"Graphics/TextureRegion.h"
	# "Graphics/Vertices.cpp"
	# "Graphics/Vertices.h"
)

set(
	INPUT_SRC
	"Input/InputLocator.cpp"
	"Input/InputLocator.h"
	"Input/InputProcessor.h"
)

set(
    LUA_SRC
    "Lua/LuaStateManager.cpp"
    "Lua/LuaStateManager.h"
    "Lua/ScriptEvent.cpp"
    "Lua/ScriptEvent.h"
	"Lua/ScriptExports.cpp"
	"Lua/ScriptExports.h"
    "Lua/ScriptSystem.cpp"
    "Lua/ScriptSystem.h"
	"Lua/Utils.h"
    # Internal exports
    "Lua/exports/LoggerExports.cpp"
    "Lua/exports/LoggerExports.h"
    "Lua/exports/EventExports.cpp"
    "Lua/exports/EventExports.h"
    "Lua/exports/EntityExports.cpp"
    "Lua/exports/EntityExports.h"
	"Lua/exports/InputExports.cpp"
	"Lua/exports/InputExports.h"
    "Lua/exports/MathExports.cpp"
    "Lua/exports/MathExports.h"
)

set(
	MAPS_SRC
	"Maps/MapLoader.cpp"
	"Maps/MapLoader.h"
)

set(
	MATH_SRC
	"Math/Vector.h"
)

set(
    MEMORY_SRC
    "Memory/loose_ptr.h"
)

set(
	PHYSICS_SRC
	"Physics/Box2DRenderer.cpp"
	"Physics/Box2DRenderer.h"
    "Physics/CollisionDispatcher.cpp"
    "Physics/CollisionDispatcher.h"
	"Physics/CollisionMasks.cpp"
	"Physics/CollisionMasks.h"
	"Physics/PhysicsLocator.cpp"
	"Physics/PhysicsLocator.h"
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
	"Systems/BaseRenderSystem.cpp"
	"Systems/BaseRenderSystem.h"
	"Systems/AnimationSystem.cpp"
	"Systems/AnimationSystem.h"
	"Systems/RenderSystem.h"
	"Systems/PhysicsSystem.cpp"
	"Systems/PhysicsSystem.h"
    "Systems/CameraFollowingSystem.cpp"
    "Systems/CameraFollowingSystem.h"
)

set(
	UTILS_SRC
	"Utils/FileSystem.cpp"
	"Utils/FileSystem.h"
	"Utils/Logger.cpp"
	"Utils/Logger.h"
	"Utils/String.cpp"
	"Utils/String.h"
	"Utils/Helpers.h"
)

# Add all current *.cpp files in to build
set(
    SOURCE_FILE_LIST;

    ${MAIN_SRC};
    ${COMPONENTS_SRC};
    ${DATA_STRUCTURES_SRC};
    ${ENTITIES_SRC};
    ${EVENTS_SRC};
    ${GRAPHICS_SRC};
    ${INPUT_SRC};
    ${LUA_SRC};
    ${MAPS_SRC};
    ${MATH_SRC};
    ${MEMORY_SRC};
    ${PHYSICS_SRC};
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

	ArtemisCpp; 	# Artemis EC System
	tinyxml2static; # TinyXML
	Box2D;			# Physics Engine
    tmxparser;		# TMX parser
    luaplus;
)

if(${UNIX})
    # Statically link boost with core for Unix Systems
    target_link_libraries(
        core;

        ${Boost_LIBRARIES};
    )
endif(${UNIX})

install(TARGETS core
    RUNTIME DESTINATION ${core_BINARY_DIR}
    ARCHIVE DESTINATION ${core_BINARY_DIR}
)
