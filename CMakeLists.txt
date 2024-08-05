PROJECT(Jimmy_Test)

CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

# Cross compile toolchain
IF (NOT PLATFORM)
    MESSAGE(FATAL_ERROR "The PLATFORM was not define!!  \n
            Use this: -DCMAKE_TOOLCHAIN_FILE=[toolchain/R16.cmake or toolchain/x86_64.cmake]")
ENDIF()
MESSAGE(STATUS "The platform : ${PLATFORM} \t CMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}")

## set output dir
SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) #set library output dir
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) #set library output dir
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) #set executable file output dir

IF (NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Release)
ENDIF ()

# find the lib directory
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib/${PLATFORM})

INCLUDE_DIRECTORIES(
        ${PROJECT_SOURCE_DIR}/src
)

# Turn On/Off the test case
ADD_SUBDIRECTORY(${PROJECT_SOURCE_DIR}/src)
