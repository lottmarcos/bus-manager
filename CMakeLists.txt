cmake_minimum_required(VERSION 3.10)

# Define the project
project(BusManager)

# Add Google Test (assuming it's already installed)
find_package(GTest REQUIRED)

# Include directories
include_directories(${GTEST_INCLUDE_DIRS})

# Add the source files
set(SOURCES 
    src/models/Data.cpp
    src/models/Database.cpp
    src/models/Onibus.cpp
    src/models/Parada.cpp
    src/models/Reserva.cpp
    src/models/Viagem.cpp
    src/services/OnibusService.cpp
    tests/Testes.cpp
)

# Create the test executable (this doesn't require a main explicitly)
add_executable(TesteCoverage ${SOURCES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")

# Link GTest and pthread
target_link_libraries(TesteCoverage ${GTEST_LIBRARIES} pthread)

# Enable testing
enable_testing()

# Add the test
add_test(NAME TesteCoverage COMMAND TesteCoverage)
