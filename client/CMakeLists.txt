cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project("boron")

option(NIX_BUILD "Building inside nix" OFF)

set(EXTERNAL_DIR deps)
add_subdirectory(${EXTERNAL_DIR}/fmt)
add_subdirectory(${EXTERNAL_DIR}/raylib)

if (${NIX_BUILD})
	add_library(runtime STATIC IMPORTED GLOBAL)
	set_target_properties(runtime PROPERTIES
	  IMPORTED_LOCATION ${RUNTIME_LIB}
	  INTERFACE_INCLUDE_DIRECTORIES ${RUNTIME_INCLUDE_DIR}
	)
	target_sources(runtime INTERFACE ${RUNTIME_SRC})
	if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
		target_link_libraries(runtime INTERFACE
			ws2_32
			userenv
			advapi32
			bcrypt
		)
	endif()
else()
	add_subdirectory(../boron_rust/client_runtime ${CMAKE_BINARY_DIR}/runtime)
endif()

set(INCLUDE_FILES include)
file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(${PROJECT_NAME}_client ${SRC_FILES})
target_link_libraries(${PROJECT_NAME}_client PRIVATE
	raylib
	runtime
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
