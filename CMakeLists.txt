# CMakeList.txt : CMake project for cmakeHopefully, include source and define
# project-specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Grader" LANGUAGES C CXX ASM)

enable_language(ASM_MASM)

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
#   Grab all CPP files from includes folder
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
set(CPP_INCLUDES_FOLDER includes)
FILE(GLOB_RECURSE CPP_SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}   "${CPP_INCLUDES_FOLDER}/*.cpp" )
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
#   Grab all ASM files from includes folder
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
set(ASM_INCLUDES_FOLDER includes)
FILE(GLOB_RECURSE ASM_SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}   "${ASM_INCLUDES_FOLDER}/*.asm" )
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

# Add source to this project's executable.
#add_executable (makeBurmaproud "cmake.cpp" "cmake.h" "test.asm")

ADD_EXECUTABLE(basic_test
    _tests/_test_files/basic_test.cpp
    ${CPP_INCLUDES_FOLDER}
    ${ASM_SOURCE_FILES}

)

ADD_EXECUTABLE(testB
    _tests/_test_files/testB.cpp
    ${CPP_INCLUDES_FOLDER}
    ${ASM_SOURCE_FILES}

)


# Set architecture to x86
if (MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:IA32")
endif()

# TODO: Add tests and install targets if needed.

# for google testing
# ------------------------------------
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

 
enable_testing() 

# Irvine32 library files
set(IRVINE32_DIR "C:/Irvine")

# link Irvine32 library & google test
target_include_directories(basic_test PRIVATE ${IRVINE32_DIR})
target_link_libraries(basic_test PRIVATE gtest ${IRVINE32_DIR}/Irvine32.lib)

target_include_directories(testB PRIVATE ${IRVINE32_DIR})
target_link_libraries(testB PRIVATE gtest ${IRVINE32_DIR}/Irvine32.lib)

#-------Only miss the sun when it starts to snow------
#-------Only know you love her when you let her go-----