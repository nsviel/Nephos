set(LIBRARY_NAME LIBRARY_RESSOURCE)

#-----------------
# Source files
#-----------------
file(GLOB_RECURSE ALL_SOURCES
  *.cpp
)

add_library(${LIBRARY_NAME} STATIC
  ${ALL_SOURCES}
)

#-----------------
# Dependencies
#-----------------
find_package(glfw3 REQUIRED)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
find_package(SQLite3 REQUIRED)

include_directories(${SQLITE3_INCLUDE_DIRS})
include_directories(${LIBGIT2_INCLUDE_DIRS})

target_link_libraries(${LIBRARY_NAME} PUBLIC
  LIBRARY_EXTERN

  ${SQLITE3_LIBRARIES}
  ${GLFW_LIBRARY}

  Eigen3::Eigen # Eigen
  -lSQLiteCpp   # sqlitecpp
  -lpthread     # sqlitecpp
  -ldl          # sqlitecpp
  -lsqlite3     # sqlite
  -lgit2        # git
  -lstdc++fs    # std::experimental::filesystem
  -lglfw        # glfw
  sqlite3
  SQLite::SQLite3
)

#-----------------
# Compilation
#-----------------
target_include_directories(${LIBRARY_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include>
  ${SQLite3_LBRARIES}
  ${LIBGIT2_LIBRARY_DIRS}
)
