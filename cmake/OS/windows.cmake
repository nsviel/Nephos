# WindowsConfig.cmake

message(STATUS "Configuring for Windows")

# Set Windows-specific compiler flags (optional)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_CRT_SECURE_NO_WARNINGS")  # Disable warnings related to secure functions

# Specify Windows libraries that need to be linked (e.g., WinSock2 for networking)
target_link_libraries(${PROJECT_NAME} PRIVATE ws2_32)

# Optionally, add custom directories for external dependencies
# For example, add an external library directory for Windows
set(EXTERNAL_LIB_DIR "C:/path/to/external/libs")
link_directories(${EXTERNAL_LIB_DIR})
