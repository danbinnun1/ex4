cmake_minimum_required(VERSION 3.0.0)
project(ex2 VERSION 0.1.0)

include(CTest)
set(C_STANDARD C99)
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic)
enable_testing()

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/matrix)


link_directories(${CMAKE_SOURCE_DIR})
link_directories(${CMAKE_SOURCE_DIR}/matrix)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")

find_package (Threads)
add_executable(ex4.out main.cpp ProblemSolver.cpp SerialServer.cpp ParallelServer.cpp crc32.c Cache.cpp ServerException.cpp ProblemInput.cpp MessageStructure.cpp AStarProblem.cpp FindGraphPath.cpp BestFSProblem.cpp BFSProblem.cpp DFSProblem.cpp GraphPathService.cpp split.cpp GraphElement.cpp MatrixCreate.cpp matrix/Matrix.cpp matrix/MatrixException.cpp ProblemException.cpp FindGraphPathInfo.cpp GraphPath.cpp file_reading.cpp)
target_link_libraries (ex3.out ${CMAKE_THREAD_LIBS_INIT})


target_link_libraries(ex3.out matrix)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)