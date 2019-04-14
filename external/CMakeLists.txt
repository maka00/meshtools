include(ExternalProject)
find_package(Git REQUIRED)
# find_package(Hg REQUIRED)

#------------------------------------------------------------------------------
# OpenMesh 8.0
#  * sets EXTERNAL_OPENMESH_INCLUDE_DIR 
#  * sets EXTERNAL_OPENMESH_LIB_DIR 

ExternalProject_Add(
    OpenMesh
    PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/OpenMesh
    GIT_REPOSITORY https://www.graphics.rwth-aachen.de:9000/OpenMesh/OpenMesh.git 
    # For shallow git clone (without downloading whole history)
    # GIT_SHALLOW 1
    # For point at certain tag
    GIT_TAG OpenMesh-8.0
    ##disables auto update on every build
    UPDATE_DISCONNECTED 0
    ##disable following
    #CONFIGURE_COMMAND "" BUILD_COMMAND "" INSTALL_DIR "" INSTALL_COMMAND ""
    INSTALL_DIR ""
    INSTALL_COMMAND cmake -E echo "Skipping install step." 
    CMAKE_ARGS -DBUILD_APPS=OFF -DCMAKE_POSITION_INDEPENDENT_CODE=ON 
    )
## Update Catch target
add_custom_target(external-OpenMesh-update
    COMMENT "Updated OpenMesh"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/OpenMesh
    COMMAND ${GIT_EXECUTABLE} pull
    DEPENDS OpenMesh)
## set include directory
set(EXTERNAL_OPENMESH_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/OpenMesh/src/OpenMesh/src" PARENT_SCOPE)
set(EXTERNAL_OPENMESH_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/OpenMesh/src/OpenMesh-build/Build/lib" PARENT_SCOPE)


#------------------------------------------------------------------------------
# GLM 
#  * sets EXTERNAL_GLM_INCLUDE_DIR 
ExternalProject_Add(
        glm
        PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        # For shallow git clone (without downloading whole history)
        GIT_SHALLOW 1
        # For point at certain tag
        # GIT_TAG 1.5.7
        #disables auto update on every build
        UPDATE_DISCONNECTED 1
        #disable following
        CONFIGURE_COMMAND "" BUILD_COMMAND "" INSTALL_DIR "" INSTALL_COMMAND ""
)
# Update spdlog target
add_custom_target(external-glm-update
        COMMENT "Updated g-turc/glm"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/glm
        COMMAND ${GIT_EXECUTABLE} pull
        DEPENDS glm)
# set include directory
set(EXTERNAL_GLM_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/glm/src/glm" PARENT_SCOPE)

#------------------------------------------------------------------------------
# nanoflann 
#  * sets EXTERNAL_NANOFLANN_INCLUDE_DIR 

ExternalProject_Add(
    nanoflann
    PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/nanoflann
    GIT_REPOSITORY https://github.com/jlblancoc/nanoflann.git
    # For shallow git clone (without downloading whole history)
    GIT_SHALLOW 1
    # For point at certain tag
    # GIT_TAG 1.5.7
    #disables auto update on every build
    #    UPDATE_DISCONNECTED 1
    #disable following
    CONFIGURE_COMMAND "" BUILD_COMMAND "" INSTALL_DIR "" INSTALL_COMMAND ""
    )
# Update spdlog target
add_custom_target(external-nanoflann-update
	    COMMENT "Updated jlblancoc/nanoflann"
	    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/nanoflann/src/nanoflann
	    COMMAND ${GIT_EXECUTABLE} pull
        DEPENDS nanoflann)
# set include directory
set(EXTERNAL_NANOFLANN_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/nanoflann/src/nanoflann/include" PARENT_SCOPE)


#------------------------------------------------------------------------------
# IMGUI 
#  * sets EXTERNAL_IMGUI_INCLUDE_DIR 
#  * sets EXTERNAL_IMGUI_SOURCES 

ExternalProject_Add(
    imgui
    PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    # For shallow git clone (without downloading whole history)
    GIT_SHALLOW 1
    # For point at certain tag
    GIT_TAG v1.69
    #disables auto update on every build
    #    UPDATE_DISCONNECTED 1
    #disable following
    CONFIGURE_COMMAND "" BUILD_COMMAND "" INSTALL_DIR "" INSTALL_COMMAND ""
    )
# Update spdlog target
add_custom_target(external-imgui-update
        COMMENT "Updated ocornut/imgui"
	    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/imgui/src/imgui
	    COMMAND ${GIT_EXECUTABLE} pull
        DEPENDS nanoflann)
# set include directory
set(EXTERNAL_NANOFLANN_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/imgui/src/imgui" PARENT_SCOPE)
set(EXTERNAL_IMGUI_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui/src/imgui/imgui.cpp"
    # "${CMAKE_CURRENT_SOURCE_DIR}/imgui/src/imgui/imgui_demo.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui/src/imgui/imgui_draw.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui/src/imgui/imgui_widgets.cpp"
    PARENT_SCOPE)

#------------------------------------------------------------------------------
# Catch - Unit test header only library
#  * sets EXTERNAL_CATCH_INCLUDE_DIR 

#ExternalProject_Add(
    #Catch
    #PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/Catch
    #GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    ## For shallow git clone (without downloading whole history)
    ## GIT_SHALLOW 1
    ## For point at certain tag
    #GIT_TAG v2.4.2
    ##disables auto update on every build
    #UPDATE_DISCONNECTED 1
    ##disable following
    #CONFIGURE_COMMAND "" BUILD_COMMAND "" INSTALL_DIR "" INSTALL_COMMAND ""
    #)
## Update Catch target
#add_custom_target(external-Catch-update
    #COMMENT "Updated Catch"
    #WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Catch/src/Catch
    #COMMAND ${GIT_EXECUTABLE} pull
    #DEPENDS Catch)
## set include directory
#set(EXTERNAL_CATCH_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Catch/src/Catch/single_include" PARENT_SCOPE)


# Examples for External Projects
#------------------------------------------------------------------------------
# nlohmann/json
#  * sets EXTERNAL_JSON_INCLUDE_DIR 

#ExternalProject_Add(
    #Json
    #PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/Json
    #GIT_REPOSITORY https://github.com/nlohmann/json.git
    ## For shallow git clone (without downloading whole history)
    ## GIT_SHALLOW 1
    ## For point at certain tag
        #GIT_TAG v3.4.0
    ##disables auto update on every build
    #UPDATE_DISCONNECTED 1
    ##disable following
    #CONFIGURE_COMMAND "" BUILD_COMMAND "" INSTALL_DIR "" INSTALL_COMMAND ""
    #)
## Update json target
#add_custom_target(external-Json-update
    #COMMENT "Updated Nlohmann/Json"
    #WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Json/src/Json
    #COMMAND ${GIT_EXECUTABLE} pull
    #DEPENDS Json)
## set include directory
#set(EXTERNAL_JSON_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Json/src/Json/single_include" PARENT_SCOPE)


#------------------------------------------------------------------------------
# spdlog
#  * sets EXTERNAL_SPDLOG_INCLUDE_DIR 

ExternalProject_Add(
    spdlog
    PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    # For shallow git clone (without downloading whole history)
    # GIT_SHALLOW 1
    # For point at certain tag
    # GIT_TAG 1.5.7
    #disables auto update on every build
    #    UPDATE_DISCONNECTED 1
    #disable following
    CONFIGURE_COMMAND "" BUILD_COMMAND "" INSTALL_DIR "" INSTALL_COMMAND ""
    )
# Update spdlog target
add_custom_target(external-spdlog-update
	    COMMENT "Updated gabime/spdlog"
	    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/spdlog/src/spdlog
	    COMMAND ${GIT_EXECUTABLE} pull
        DEPENDS spdlog)
# set include directory
set(EXTERNAL_SPDLOG_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/spdlog/src/spdlog/include" PARENT_SCOPE)

#
# #------------------------------------------------------------------------------
# # whoshuu/cpr
# # C++ http requests library
# #  * sets CPR_INCLUDE_DIR 
# #  * sets CPR_LIBRARIES 
#
# ExternalProject_Add(
#     Cpr-ext
#     PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/cpr
#     GIT_REPOSITORY https://github.com/whoshuu/cpr.git
#     # For shallow git clone (without downloading whole history)
#     # GIT_SHALLOW 1
#     # For point at certain tag
#     # GIT_TAG 1.5.7
#     #disables auto update on every build
#     UPDATE_DISCONNECTED 1
#     #disable install step
#     INSTALL_DIR "" INSTALL_COMMAND ""
#     )
# set(CPR_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/cpr/src/Cpr-ext/include CACHE
#     INTERNAL "")
# set(CPR_LIBRARIES
#     ${CMAKE_CURRENT_SOURCE_DIR}/cpr/src/Cpr-ext-build/lib/libcpr.a curl CACHE
#     INTERNAL "")
#
# # Update cpr target
# add_custom_target(external-cpr-update
#     COMMENT "Updated whoshuu/cpr"
#     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/cpr/src/cpr
#     COMMAND ${GIT_EXECUTABLE} pull
#     DEPENDS Cpr-ext)
#
# # Uset this with:
# # target_include_directories(your_target_name ${CPR_INCLUDE_DIRS})
# # target_link_libraries(your_target_name ${CPR_LIBRARIES})

#------------------------------------------------------------------------------
# Convenience update all
add_custom_target(external-update-all
    COMMENT "Updated all external projects"
    DEPENDS external-OpenMesh-update)

add_custom_target(update
    COMMENT "Updated all external projects"
    DEPENDS external-update-all)
