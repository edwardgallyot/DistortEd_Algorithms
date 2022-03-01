cmake_minimum_required(VERSION 3.20)
project(Wave_io)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_SOURCE_DIR /home/edgallyot/drives/2TB_SSD/Documents/UWL/Semester_2/Programming/DistortEd_Algorithms)



add_subdirectory(DistortEd_Algorithms)

add_executable(Wave_io main.cpp)

include_directories(Wave_io
        DistortEd_Algorithms
        )

target_link_libraries(Wave_io
        DistortEd_Algorithmslib
        )