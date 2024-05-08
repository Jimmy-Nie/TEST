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

ADD_SUBDIRECTORY(signal)

#Generate the lib and executable file
SET(BIN_NAME test_future)
ADD_EXECUTABLE(${BIN_NAME} test_future.cpp)
TARGET_LINK_LIBRARIES(${BIN_NAME} PUBLIC pthread dl)

SET(BIN_NAME test_function)
ADD_EXECUTABLE(${BIN_NAME} test_function.cpp)
TARGET_LINK_LIBRARIES(${BIN_NAME} PUBLIC pthread dl)

SET(BIN_NAME test_smart_ptr)
ADD_EXECUTABLE(${BIN_NAME} test_smart_ptr.cpp)
TARGET_LINK_LIBRARIES(${BIN_NAME} PUBLIC pthread dl)

SET(BIN_NAME test_thread)
ADD_EXECUTABLE(${BIN_NAME} test_thread.cpp)
TARGET_LINK_LIBRARIES(${BIN_NAME} PUBLIC pthread dl)

SET(BIN_NAME test_signal)
ADD_EXECUTABLE(${BIN_NAME} test_signal.cpp)
TARGET_LINK_LIBRARIES(${BIN_NAME} PUBLIC pthread dl)

SET(BIN_NAME test_args)
ADD_EXECUTABLE(${BIN_NAME} test_args.cpp)
TARGET_LINK_LIBRARIES(${BIN_NAME} PUBLIC pthread dl)

SET(BIN_NAME test_functor)
ADD_EXECUTABLE(${BIN_NAME} test_functor.cpp)
TARGET_LINK_LIBRARIES(${BIN_NAME} PUBLIC pthread dl)

SET(BIN_NAME test_time)
ADD_EXECUTABLE(${BIN_NAME} ${BIN_NAME}.cpp)
TARGET_LINK_LIBRARIES(${BIN_NAME} PUBLIC pthread dl)

SET(BIN_NAME test_log)
ADD_EXECUTABLE(${BIN_NAME} ${BIN_NAME}.cpp)
TARGET_LINK_LIBRARIES(${BIN_NAME} PUBLIC pthread dl)