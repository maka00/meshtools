cmake_minimum_required(VERSION 3.9)
project(common-lib)

if(MSVC)
    add_compile_options("/W4" "$<$<CONFIG:RELEASE>:/O2>")
else()
	# for the hardcore type of guy...
	#add_compile_options("-Wall" "-Wextra" "-Werror" "$<$<CONFIG:RELEASE>:-O3>")
	add_compile_options("$<$<CONFIG:RELEASE>:-O3>")
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	    # add_compile_options("-stdlib=libc++")
	    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -v")
	    # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")
    else()
        # nothing special for gcc at the moment
    endif()
endif()
if (WIN32)
	SET (Boost_USE_STATIC_LIBS ON)
endif(WIN32)

find_package(Threads)
find_package(Boost) # COMPONENTS filesystem iostreams system program_options REQUIRED)


if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-D_DEBUG=1)
endif()

add_library(${PROJECT_NAME} INTERFACE )

target_sources(${PROJECT_NAME} INTERFACE
)

target_include_directories(${PROJECT_NAME} INTERFACE
    ${PROJECT_SOURCE_DIR}/include
)
