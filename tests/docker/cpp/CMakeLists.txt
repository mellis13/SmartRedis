project(DockerTester)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_CXX_STANDARD 17)

find_library(SR_LIB smartredis)

include_directories(SYSTEM
    /usr/local/include/smartredis
)

# Build executables

add_executable(docker_test
	test_docker.cpp
)
target_link_libraries(docker_test ${SR_LIB} pthread)