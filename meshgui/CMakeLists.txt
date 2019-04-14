cmake_minimum_required(VERSION 3.9)
project(meshgui)

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
set(SOURCES main.cpp shader.cpp shader.h camera.cpp camera.h helper.h application.cpp application.h)

if (WIN32)
	SET (Boost_USE_STATIC_LIBS ON)
endif(WIN32)
set(OpenGL_GL_PREFERENCE GLVND)

find_package(Threads)
find_package(Boost COMPONENTS filesystem iostreams system program_options REQUIRED)
find_package(OpenGL)
find_package(glfw3 REQUIRED)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-D_DEBUG=1)
endif()
set(IMGUI_FILES imgui.cpp imgui_draw.cpp imgui_widgets.cpp imgui_impl_glfw.cpp imgui_impl_opengl3.cpp  )
add_executable(${PROJECT_NAME} ${SOURCES} ${IMGUI_FILES} ${PROJECT_SOURCE_DIR}/GLAD/src/glad.c)

set_target_properties(${PROJECT_NAME}
        PROPERTIES
        DEBUG_POSTFIX "d"
        CXX_STANDARD 17
        # CXX_EXTENSIONS OFF
        CMAKE_CXX_FLAGS_RELEASE "-O3"
        IMPORTED_LOCATION "${EXTERNAL_OPENMESH_LIB_DIR}/libOpenMeshCore.so"
        IMPORTED_LOCATION "${EXTERNAL_OPENMESH_LIB_DIR}/libOpenMeshTools.so"
        )

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${PROJECT_SOURCE_DIR}

        PRIVATE
        ${OPENGL_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}/GLAD/include
        ${EXTERNAL_IMGUI_INCLUDE_DIR}
        ${EXTERNAL_SPDLOG_INCLUDE_DIR}
        ${EXTERNAL_STB_INCLUDE_DIR}
        ${EXTERNAL_GLM_INCLUDE_DIR}
        ${EXTERNAL_NANOFLANN_INCLUDE_DIR}
        ${EXTERNAL_OPENMESH_INCLUDE_DIR}
        ${BOOST_INCLUDE_DIRS}
        ${CMAKE_CURRENT_BINARY_DIR}
        
        )
# CMake 3.14 onwards
target_link_directories(${PROJECT_NAME}
        PRIVATE
        ${EXTERNAL_OPENMESH_LIB_DIR}
        ../lib
)


target_link_libraries(${PROJECT_NAME}
        PUBLIC
        Threads::Threads
        OpenMeshCore
        OpenMeshTools
        common-lib
        Boost::program_options
        Boost::filesystem
        glfw
        ${OPENGL_LIBRARIES}
        ${CMAKE_DL_LIBS}
        )
target_compile_features(${PROJECT_NAME}
        PUBLIC
        cxx_std_17
        )

target_compile_options(${PROJECT_NAME}
        PUBLIC
        )
