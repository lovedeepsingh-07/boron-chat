cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project("boron")

set(EXTERNAL_DIR deps)
add_subdirectory(${EXTERNAL_DIR}/fmt)
add_subdirectory(net ${CMAKE_BINARY_DIR}/net)
add_subdirectory(${EXTERNAL_DIR}/raylib)

# ------ boron_client ------
set(INCLUDE_FILES include)
file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(${PROJECT_NAME}_client ${SRC_FILES})
target_link_libraries(${PROJECT_NAME}_client PRIVATE
	raylib
	net
	fmt::fmt
)
target_include_directories(${PROJECT_NAME}_client PRIVATE
	${EXTERNAL_DIR}/flatbuffers/include
	${EXTERNAL_DIR}/clay
	${INCLUDE_FILES}
)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")
	target_compile_definitions(${PROJECT_NAME}_client PRIVATE PLATFORM_DESKTOP)
endif()
