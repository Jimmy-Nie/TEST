FILE(GLOB_RECURSE SRCs
        "*.c*"
        "*.h*"
)
SET(BIN_NAME signal)
ADD_EXECUTABLE(${BIN_NAME} ${SRCs})
TARGET_LINK_LIBRARIES(${BIN_NAME} PUBLIC pthread dl)