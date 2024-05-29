FILE(GLOB_RECURSE SRCs
        "*.c*"
        "*.h*"
)
SET(LIB_NAME signal)
ADD_LIBRARY(${LIB_NAME} ${SRCs})