# this is required
SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_PROCESSOR arm)

# set platform define
SET(PLATFORM R16) #根据自己的环境去修改该处

# specify the cross compiler
SET(tools /usr/local/toolchain/${PLATFORM})

SET(CMAKE_C_COMPILER  ${tools}/bin/arm-openwrt-linux-gcc)
SET(CMAKE_CXX_COMPILER ${tools}/bin/arm-openwrt-linux-g++)

#-----------------------------------------------------------
# where is the target environment (Only in toolchain directory)
#-----------------------------------------------------------
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)