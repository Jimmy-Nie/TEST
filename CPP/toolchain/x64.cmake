# this is required
SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_PROCESSOR x86)

# set platform define
ADD_DEFINITIONS(-DPC)

SET(PLATFORM x64)

# specify the cross compiler
SET(CMAKE_C_COMPILER  gcc)
SET(CMAKE_CXX_COMPILER g++)
#-----------------------------------------------------------
# where is the target environment (Only in toolchain directory)
#-----------------------------------------------------------
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)