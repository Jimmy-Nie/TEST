SET(target "zlib")

FILE(GLOB_RECURSE ZLIB_SRC "./*.c*" "./*.h*")

IF (CMAKE_BUILD_TYPE MATCHES "Debug")
    MESSAGE("${target} Debug -g -O0 -rdynamic")
    SET(CMAKE_CXX_FLAGS_DEBUG "-g -O0")# -g show more info for debug
ELSE ()
    MESSAGE("${target} Release")
    SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -s")#-Wall show all the warning
ENDIF ()

SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PLATFORM}/lib)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PLATFORM}/lib)


ADD_LIBRARY(${target} SHARED ${ZLIB_SRC})
TARGET_LINK_LIBRARIES(${target} PUBLIC pthread dl)