project(tmxparser)

include_directories(
    .;
    tinyxml/;
)

set(
    MAIN_SRC
    "TmxParser/Tmx.h"
    # Obj
    "TmxParser/TmxEllipse.cpp"
    "TmxParser/TmxEllipse.h"
    "TmxParser/TmxPoint.h"
    "TmxParser/TmxPolygon.cpp"
    "TmxParser/TmxPolygon.h"
    "TmxParser/TmxPolyline.cpp"
    "TmxParser/TmxPolyline.h"
    "TmxParser/TmxObject.cpp"
    "TmxParser/TmxObject.h"
    "TmxParser/TmxObjectGroup.cpp"
    "TmxParser/TmxObjectGroup.h"
    # Image
    "TmxParser/TmxImage.cpp"
    "TmxParser/TmxImage.h"
    "TmxParser/TmxImageLayer.cpp"
    "TmxParser/TmxImageLayer.h"
    # Layers
    "TmxParser/TmxLayer.cpp"
    "TmxParser/TmxLayer.h"
    # Map stuff
    "TmxParser/TmxMap.cpp"
    "TmxParser/TmxMap.h"
    # Properties
    "TmxParser/TmxPropertySet.cpp"
    "TmxParser/TmxPropertySet.h"
    # Tiles
    "TmxParser/TmxMapTile.h"
    "TmxParser/TmxTile.cpp"
    "TmxParser/TmxTile.h"
    "TmxParser/TmxTileset.cpp"
    "TmxParser/TmxTileset.h"
    # Misc
    "TmxParser/TmxUtil.cpp"
    "TmxParser/TmxUtil.h"
)

set(
    TINYXML_SRC
    "TmxParser/tinyxml/tinystr.cpp"
    "TmxParser/tinyxml/tinystr.h"
    "TmxParser/tinyxml/tinyxml.cpp"
    "TmxParser/tinyxml/tinyxml.h"
    "TmxParser/tinyxml/tinyxmlerror.cpp"
    "TmxParser/tinyxml/tinyxmlparser.cpp"
)

set(
    BASE_64_SRC
    "TmxParser/base64/base64.cpp"
    "TmxParser/base64/base64.h"
)

set(
    ZLIB_SRC
    "TmxParser/zlib/adler32.c"
    "TmxParser/zlib/compress.c"
    "TmxParser/zlib/crc32.c"
    "TmxParser/zlib/crc32.h"
    "TmxParser/zlib/deflate.c"
    "TmxParser/zlib/deflate.h"
    "TmxParser/zlib/gzclose.c"
    "TmxParser/zlib/gzguts.h"
    "TmxParser/zlib/gzlib.c"
    "TmxParser/zlib/gzread.c"
    "TmxParser/zlib/gzwrite.c"
    "TmxParser/zlib/infback.c"
    "TmxParser/zlib/inffast.c"
    "TmxParser/zlib/inffast.h"
    "TmxParser/zlib/inffixed.h"
    "TmxParser/zlib/inflate.c"
    "TmxParser/zlib/inflate.h"
    "TmxParser/zlib/inftrees.c"
    "TmxParser/zlib/inftrees.h"
    "TmxParser/zlib/trees.c"
    "TmxParser/zlib/trees.h"
    "TmxParser/zlib/uncompr.c"
    "TmxParser/zlib/zconf.h"
    "TmxParser/zlib/zlib.h"
    "TmxParser/zlib/zutil.c"
    "TmxParser/zlib/zutil.h"
)

set(
    SOURCES;
    ${MAIN_SRC};
    ${TINYXML_SRC};
    ${BASE_64_SRC};
    ${ZLIB_SRC};
)

add_library(
    tmxparser
    STATIC
    ${SOURCES}
)
