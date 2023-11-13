set(LIBRARY_NAME LIBRARY_UTILITY)

#-----------------
# Source files
#-----------------
file(GLOB_RECURSE ALL_SOURCES *.cpp *.h)

#-----------------
# Compilation
#-----------------
add_library(${LIBRARY_NAME} STATIC ${ALL_SOURCES})

#-----------------
# Dependencies
#-----------------
find_package(glfw3 REQUIRED)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package(SQLite3 REQUIRED)

target_link_libraries(${LIBRARY_NAME} PUBLIC
  LIBRARY_EXTERN

  Eigen3::Eigen # Eigen
  -lSQLiteCpp   # sqlitecpp
  -lpthread     # sqlitecpp
  -ldl          # sqlitecpp
  -lsqlite3     # sqlite
  -lgit2        # git
  -lstdc++fs    # std::experimental::filesystem
  -lglfw        # glfw
  -lsqlite3     # sqlite
)

target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
