IF (CMAKE_BUILD_TYPE MATCHES "Debug")
    MESSAGE("Debug -g -O0 -rdynamic")
    SET(CMAKE_CXX_FLAGS_DEBUG "-g -O0")# -g show more info for debug
ELSE ()
    MESSAGE("Release -O3 -s")
    SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -s")#-Wall show all the warning
ENDIF ()

FILE(GLOB_RECURSE SRCs
        "*.c*"
        "*.h*"
)

LINK_LIBRARIES()

#Generate the lib and executable file
SET(BIN_NAME sort)
ADD_EXECUTABLE(${BIN_NAME} sort.cpp)