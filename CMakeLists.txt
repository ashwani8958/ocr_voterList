cmake_minimum_required(VERSION 3.28)

project(voterList  VERSION 0.1 LANGUAGES CXX)

# -----------------------------
# C++ standard
# -----------------------------
set(CMAKE_CXX_STANDARD 17)

# -----------------------------
# C++ Build Type
# -----------------------------
set(CMAKE_BUILD_TYPE Debug)

# -----------------------------
# Find Poppler (C++ API)
# -----------------------------
find_package(PkgConfig REQUIRED)
pkg_check_modules(POPPLER_CPP REQUIRED poppler-cpp)

# -----------------------------
# Find OpenCV
# -----------------------------
find_package(OpenCV REQUIRED)

# -----------------------------
# Include directories
# -----------------------------
include_directories(
    ${POPPLER_CPP_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
)

set(SOURCES 
    src/main.cpp
    src/ExtractImage.cpp
)

add_executable(voterList ${SOURCES})

# -----------------------------
# Link libraries
# -----------------------------
target_link_libraries(voterList
    ${POPPLER_CPP_LIBRARIES}
    ${OpenCV_LIBS}
)

# -----------------------------
# Compiler warnings
# -----------------------------
target_compile_options(voterList PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)