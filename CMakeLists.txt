cmake_minimum_required (VERSION 3.14)
project ("segment_distance")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

add_subdirectory(geometry)

# Add source to this project's executable.
add_executable (segment_distance "main.cpp")

target_link_libraries(segment_distance geometry)

include(FetchContent)
FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
)
FetchContent_MakeAvailable(argparse)

target_link_libraries(segment_distance argparse)

option(SEGMENT_DISTANSE_TESTING "Enable tests." ON)

if(SEGMENT_DISTANSE_TESTING)
	include(CTest)
	add_subdirectory(test)
endif()
