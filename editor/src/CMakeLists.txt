find_package(Qt QUIET REQUIRED)

set(CMAKE_AUTOMOC ON)

include_directories(
	# Subdir include
	${CMAKE_CURRENT_SOURCE_DIR};
	${CMAKE_CURRENT_BINARY_DIR};
)

include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

set(
	QT_WIDGETS_SRC
	"QtWidgets/QSFMLCanvas.cpp"
	"QtWidgets/QSFMLCanvas.h"
)

set(
	MAIN_SRC
	"main.cpp"
)

set(
	SOURCE_FILE_LIST;

	${MAIN_SRC};
	${QT_WIDGETS_SRC};
)

add_executable(
	editor 
	
	${SOURCE_FILE_LIST} 
)

target_link_libraries(
	editor 
	
	${QT_LIBRARIES}
) 