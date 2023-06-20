execute_process(COMMAND bash -c "clear\n")
cmake_minimum_required(VERSION 3.0)

project(
	ChatApp 
	VERSION 1.0
	LANGUAGES CXX	
)

execute_process(
	COMMAND bash -c "echo \$(basename \"\$PWD\")"
	OUTPUT_VARIABLE BUILD_TYPE
	OUTPUT_STRIP_TRAILING_WHITESPACE
)



if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(EXECUTABLE_EXTENSION ".so")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(EXECUTABLE_EXTENSION ".exe")
else()
    set(EXECUTABLE_EXTENSION "")
    # message(FATAL_ERROR "Operating System UnSupport: ${CMAKE_SYSTEM_NAME}")
endif()




set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/${BUILD_TYPE}/)
set(OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY}/dist)
set(WEBSOCKETPP_INCLUDE_DIR ${LIB_DIR}/websocketpp/websocketpp)

add_subdirectory(${LIB_DIR}/websocketpp)
set(WEBSOCKETPP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/websocketpp)
find_package(Boost COMPONENTS system REQUIRED)
find_package(Boost COMPONENTS thread REQUIRED)
include_directories(${WEBSOCKETPP_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)


if("${BUILD_TYPE}" STREQUAL "server")
	set(BUILD_SOURCES
		${SOURCE_DIR}/main.cpp
		${SOURCE_DIR}/socket.cpp
	)
elseif("${BUILD_TYPE}" STREQUAL "client")
	set(BUILD_SOURCES
		${SOURCE_DIR}/main.cpp
		${SOURCE_DIR}/user.cpp
		${SOURCE_DIR}/socket/socket.cpp
		${SOURCE_DIR}/socket/metadata.cpp
	)
endif()

add_executable(${BUILD_TYPE} ${BUILD_SOURCES})
set_target_properties(${BUILD_TYPE} PROPERTIES OUTPUT_NAME "${BUILD_TYPE}${EXECUTABLE_EXTENSION}")
target_link_libraries(${BUILD_TYPE} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib/websocketpp Boost::thread)

if("${BUILD_TYPE}" STREQUAL "server")
	execute_process(COMMAND bash -c "echo -e \"\\n\\033[0;36m==========================================================\"")
	execute_process(COMMAND bash -c "echo -e \"= \\033[0;36m-------------------- \\033[5;34mBUILD SERVER\\033[0;36m -------------------- =\\033[0m\"")
	execute_process(COMMAND bash -c "echo -e \"\\033[0;36m==========================================================\\033[0m\"")
else()
	execute_process(COMMAND bash -c "echo -e \"\\n\\033[0;34m==========================================================\"")
	execute_process(COMMAND bash -c "echo -e \"= \\033[0;34m-------------------- \\033[5;36mBUILD CLIENT\\033[0;34m -------------------- =\\033[0m\"")
	execute_process(COMMAND bash -c "echo -e \"\\033[0;34m==========================================================\\033[0m\"")
endif()