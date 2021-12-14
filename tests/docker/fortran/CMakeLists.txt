project(DockerTester)

cmake_minimum_required(VERSION 3.10)

enable_language(Fortran)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 99)

set(ftn_client_src
    /usr/local/src/SmartRedis/src/fortran/fortran_c_interop.F90
    /usr/local/src/SmartRedis/src/fortran/dataset.F90
    /usr/local/src/SmartRedis/src/fortran/client.F90
)

find_library(SR_LIB smartredis)

include_directories(SYSTEM
    /usr/local/include/smartredis
)

add_executable(docker_test
	test_docker.F90
	${ftn_client_src}
)

target_link_libraries(docker_test ${SR_LIB} pthread)