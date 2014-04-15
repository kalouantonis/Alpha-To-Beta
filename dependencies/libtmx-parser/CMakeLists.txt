project(tmxparser)

include_directories(
	.;
#	${ALPHA_TO_BETA_SOURCE_DIR}/dependencies/tinyxml2;
    ${tinyxml2_SOURCE_DIR};
)

SET(
	MAIN_SRC
    "tmxparser.cpp"
	"tmxparser.h"
)

add_library(
    tmxparser
    STATIC
  	${MAIN_SRC}
 )
