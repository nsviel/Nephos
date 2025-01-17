# MacOSConfig.cmake

message(STATUS "Configuring for macOS")

# Set macOS-specific compiler flags (for example, enabling C++17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

# macOS-specific libraries (for example, linking with CoreFoundation and Cocoa)
find_library(COREFOUNDATION CoreFoundation REQUIRED)
find_library(COCOA Cocoa REQUIRED)

# Link with CoreFoundation and Cocoa libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${COREFOUNDATION} ${COCOA})

# Optionally, set a deployment target (for example, macOS 10.12)
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.12" CACHE STRING "Minimum macOS deployment version")

# Set the system-specific SDK path for macOS
set(CMAKE_OSX_SYSROOT "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk")

# Add macOS-specific include directories (if needed)
include_directories("/path/to/mac-specific/include")

# Any additional macOS-specific settings can be added here
