
cmake_minimum_required(VERSION 2.8)

if(DEFINED ENV{BUILT_TOOLS})	  
    set (BUILT_TOOLS $ENV{BUILT_TOOLS} )
else()
        message(FATAL_ERROR "BUILT_TOOLS VARIABLE NOT SET")
endif()

if(DEFINED ENV{BUILT_TOOLS_ARCH}) 
	  
set (BUILT_TOOLS_ARCH $ENV{BUILT_TOOLS_ARCH})
else()
    message(FATAL_ERROR "BUILT_TOOLS_ARCH VARIABLE NOT SET")
endif()

if (APPLE)
    if (DEFINED ENV{MACPORTS_PREFIX}) 
        set (MACPORTS_PREFIX $ENV{MACPORTS_PREFIX} )
    else()
        message(FATAL_ERROR "MACPORTS_PREFIX must be set for apple platform")
    endif()
endif(APPLE)




if (APPLE) 
    set (CLANG_PREFIX ${BUILT_TOOLS_ARCH})
    set (GMP_PREFIX ${MACPORTS_PREFIX})
    set (LLVM_PREFIX ${BUILT_TOOLS_ARCH})
    message(STATUS "LLVM_PREFIX is ${BUILT_TOOLS_ARCH}") 
elseif(APPLE) 
    set (CLANG_PREFIX /cas/apps/llvm-3.0)
    set (GMP_PREFIX ${BUILT_TOOLS_ARCH}) 
    set (LLVM_PREFIX ${BUILT_TOOLS_ARCH})
endif(APPLE)

find_package(Boost 1.52 COMPONENTS program_options system filesystem unit_test_framework REQUIRED)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(Boost_ALL_DYN_LINK ON)

include_directories(
  ${Boost_INCLUDE_DIR}
  )

set (CMAKE_PREFIX_PATH ${BUILT_TOOLS_ARCH})

set (CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src/cmake)


find_package(Cloog REQUIRED)
find_package(OSL REQUIRED)
find_package(gmp REQUIRED)

add_definitions(-DCLOOG_INT_GMP)
include_directories(${CMAKE_SOURCE_DIR}/src/include)
include_directories(${CLOOG_INCLUDE_DIR})



add_subdirectory(src)
add_subdirectory(test)