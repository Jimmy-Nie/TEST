# this is required
SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_PROCESSOR arm)

# set platform define
ADD_DEFINITIONS(-DR328)

SET(PLATFORM R328)

# specify the cross compiler
SET(TOOLCHAIN_DIR /usr/local/toolchain/${PLATFORM}) #根据自己的环境去修改该处

SET(CMAKE_C_COMPILER  ${TOOLCHAIN_DIR}/bin/arm-openwrt-linux-gcc)
SET(CMAKE_CXX_COMPILER ${TOOLCHAIN_DIR}/bin/arm-openwrt-linux-g++)
SET(CMAKE_AR_COMPILER ${TOOLCHAIN_DIR}/bin/arm-openwrt-linux-ar)

#-----------------------------------------------------------
# where is the target environment (Only in toolchain directory)
#-----------------------------------------------------------
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)