add_library(sgp4 STATIC)
add_library(${PROJECT_NAME}::sgp4 ALIAS sgp4)

target_sources(sgp4
  PRIVATE
    sgp4ext.cpp
    sgp4io.cpp
    sgp4unit.cpp
)

set_target_properties(sgp4 PROPERTIES
  POSITION_INDEPENDENT_CODE TRUE
)

target_include_directories(sgp4
  SYSTEM PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
