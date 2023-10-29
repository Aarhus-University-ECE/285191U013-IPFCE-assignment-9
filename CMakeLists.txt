cmake_minimum_required(VERSION 3.16)
project(assignment-9 VERSION 0.1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20) # Needed to use designated initializers in ./tests/tests.cpp
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
		Catch2
		GIT_REPOSITORY https://github.com/catchorg/Catch2.git
		GIT_TAG        v3.0.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

add_library(sum STATIC sum.c)
add_library(search STATIC search.c)
add_library(dfs STATIC dfs.c)

set(libs sum search dfs)

foreach(lib ${libs})
	target_compile_definitions(${lib} PUBLIC -DTEST)
	target_compile_options(${lib}
		PUBLIC
		$<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wall -Wpedantic>
	)
	target_compile_options(${lib} PRIVATE -Wno-comment)
endforeach()

add_executable(unit-tests tests/tests.cpp)
target_include_directories(unit-tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(unit-tests ${libs})
target_link_libraries(unit-tests Catch2::Catch2WithMain)
target_compile_options(unit-tests PRIVATE -Wno-comment)

