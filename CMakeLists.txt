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

# ------ boron_common ------
set(COMMON_INCLUDE_FILES
	common/include
)
file(GLOB_RECURSE COMMON_SRC_FILES common/src/*.cpp)
add_library(${PROJECT_NAME}_common ${COMMON_SRC_FILES})
target_link_libraries(${PROJECT_NAME}_common PUBLIC
	net
	fmt::fmt
)
target_include_directories(${PROJECT_NAME}_common PUBLIC
	${EXTERNAL_DIR}/flatbuffers/include
	${COMMON_INCLUDE_FILES}
	${EXTERNAL_DIR}/clay
)

# ------ boron_server ------
set(SERVER_INCLUDE_FILES server/include)
file(GLOB_RECURSE SERVER_SRC_FILES server/src/*.cpp)
add_executable(${PROJECT_NAME}_server ${SERVER_SRC_FILES})
target_link_libraries(${PROJECT_NAME}_server PRIVATE
	${PROJECT_NAME}_common
)
target_include_directories(${PROJECT_NAME}_server PRIVATE
	${SERVER_INCLUDE_FILES}
)

# ------ boron_client ------
set(CLIENT_INCLUDE_FILES client/include)
file(GLOB_RECURSE CLIENT_SRC_FILES client/src/*.cpp)
add_executable(${PROJECT_NAME}_client ${CLIENT_SRC_FILES})
target_link_libraries(${PROJECT_NAME}_client PRIVATE
	${PROJECT_NAME}_common
	raylib
)
target_include_directories(${PROJECT_NAME}_client PRIVATE
	${CLIENT_INCLUDE_FILES}
)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")
	target_compile_definitions(${PROJECT_NAME}_server PRIVATE PLATFORM_DESKTOP)
	target_compile_definitions(${PROJECT_NAME}_client PRIVATE PLATFORM_DESKTOP)
endif()
