IF (CMAKE_BUILD_TYPE MATCHES "Debug")
    MESSAGE("Debug -g -O0 -rdynamic")
    SET(CMAKE_CXX_FLAGS_DEBUG "-g -O0")# -g show more info for debug
ELSE ()
    MESSAGE("Release -O3 -s")
    SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -s")#-Wall show all the warning
ENDIF ()

LINK_LIBRARIES(libpthread.so libdl.so)

#Generate the lib and executable file
SET(BIN_NAME test_future)
ADD_EXECUTABLE(${BIN_NAME} test_future.cpp)

SET(BIN_NAME test_function)
ADD_EXECUTABLE(${BIN_NAME} test_function.cpp)

SET(BIN_NAME test_smart_ptr)
ADD_EXECUTABLE(${BIN_NAME} test_smart_ptr.cpp)

SET(BIN_NAME test_thread)
ADD_EXECUTABLE(${BIN_NAME} test_thread.cpp)

SET(BIN_NAME test_args)
ADD_EXECUTABLE(${BIN_NAME} test_args.cpp)

SET(BIN_NAME test_functor)
ADD_EXECUTABLE(${BIN_NAME} test_functor.cpp)

SET(BIN_NAME test_time)
ADD_EXECUTABLE(${BIN_NAME} ${BIN_NAME}.cpp)

SET(BIN_NAME test_log)
ADD_EXECUTABLE(${BIN_NAME} ${BIN_NAME}.cpp)

SET(BIN_NAME test_static)
ADD_EXECUTABLE(${BIN_NAME} ${BIN_NAME}.cpp)

SET(BIN_NAME test_string)
ADD_EXECUTABLE(${BIN_NAME} ${BIN_NAME}.cpp)

SET(BIN_NAME test_template_meta)
ADD_EXECUTABLE(${BIN_NAME} ${BIN_NAME}.cpp)

SET(BIN_NAME test_mutable)
ADD_EXECUTABLE(${BIN_NAME} ${BIN_NAME}.cpp)

SET(BIN_NAME test_exception)
ADD_EXECUTABLE(${BIN_NAME} ${BIN_NAME}.cpp)


FILE(GLOB_RECURSE Stack_SRCs
        "stack/*.c*"
        "stack/*.h*"
        )
SET(BIN_NAME test_stack_trace)
ADD_EXECUTABLE(${BIN_NAME} ${BIN_NAME}.cpp ${Stack_SRCs})

SET(BIN_NAME test_cpu_frequency)
ADD_EXECUTABLE(${BIN_NAME} ${BIN_NAME}.cpp ${Stack_SRCs})
TARGET_LINK_LIBRARIES(${BIN_NAME} PUBLIC pthread dl)

SET(BIN_NAME test_clock)
ADD_EXECUTABLE(${BIN_NAME} ${BIN_NAME}.cpp ${Stack_SRCs})

SET(BIN_NAME test_lock)
ADD_EXECUTABLE(${BIN_NAME} ${BIN_NAME}.cpp)
TARGET_LINK_LIBRARIES(${BIN_NAME} PUBLIC pthread dl)

SET(BIN_NAME test_priority)
ADD_EXECUTABLE(${BIN_NAME} ${BIN_NAME}.cpp)
TARGET_LINK_LIBRARIES(${BIN_NAME} PUBLIC pthread dl)