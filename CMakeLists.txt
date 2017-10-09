cmake_minimum_required(VERSION 3.1)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

project(NIFTY_META)
set(${PROJECT_NAME}_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

#-------------------------------------------------------------------------------------------------------------------
# Version
#-------------------------------------------------------------------------------------------------------------------
# as seen in the github.com/QuantStack/xtensor
file(STRINGS "${${PROJECT_NAME}_INCLUDE_DIR}/nifty/meta/meta_config.hpp" ${PROJECT_NAME}_version_defines
     REGEX "#define ${PROJECT_NAME}_VERSION_(MAJOR|MINOR|PATCH)")
foreach(ver ${${PROJECT_NAME}_version_defines})
    if(ver MATCHES "#define ${PROJECT_NAME}_VERSION_(MAJOR|MINOR|PATCH) +([^ ]+)$")
        set(${PROJECT_NAME}_VERSION_${CMAKE_MATCH_1} "${CMAKE_MATCH_2}" CACHE INTERNAL "")
    endif()
endforeach()
set(${PROJECT_NAME}_VERSION 
    ${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_PATCH})
message(STATUS "${PROJECT_NAME} v${${PROJECT_NAME}_VERSION}")



include(CheckCXXCompilerFlag)


SET(BUILD_TESTS    ON CACHE BOOL "Build the test suite ?"   FORCE)
SET(BUILD_DOCS     ON CACHE BOOL "Build the documentation?" FORCE)
SET(BUILD_EXAMPLES ON CACHE BOOL "Build the examples?"      FORCE)

#-------------------------------------------------------------------------------------------------------------------
# cmake packages
#-------------------------------------------------------------------------------------------------------------------
include(ExternalProject)

#-------------------------------------------------------------------------------------------------------------------
# check for c++ 14 support
#-------------------------------------------------------------------------------------------------------------------

# FIXME c++14 checks are broken???
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    CHECK_CXX_COMPILER_FLAG("-std=c++14" HAS_CPP14_FLAG)
    #CHECK_CXX_COMPILER_FLAG("-std=c++11" HAS_CPP11_FLAG)
    if (HAS_CPP14_FLAG)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
    else()
        message(FATAL_ERROR "Unsupported compiler -- multi-array  requires C++14 support!")
    endif()
endif()


if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()

#-------------------------------------------------------------------------------------------------------------------
# threading package
#-------------------------------------------------------------------------------------------------------------------
find_package(Threads REQUIRED)

#-------------------------------------------------------------------------------------------------------------------
# include include files
#-------------------------------------------------------------------------------------------------------------------
file(GLOB_RECURSE headers include/*.hxx)
include_directories(include)


#-------------------------------------------------------------------------------------------------------------------
# external projects which need to be in the `include tree`
#-------------------------------------------------------------------------------------------------------------------


# #---------------------------------------------------
# # Boost header Only
# #---------------------------------------------------
# ExternalProject_Add(
#     external_boost_header_only
#     PREFIX ${CMAKE_BINARY_DIR}/external_projects/boost
#     GIT_REPOSITORY https://github.com/NumScale/boost-header-only
#     GIT_TAG 3a7ee7dfafa2a484511289aab5a4f5344bdcf8d7
#     TIMEOUT 5
#     #UPDATE_COMMAND ${GIT_EXECUTABLE} pull
#     CONFIGURE_COMMAND ""
#     BUILD_COMMAND ""
#     INSTALL_COMMAND ""
#     LOG_DOWNLOAD ON
# )
# # Expose required variable (DOCTEST_INCLUDE_DIR) to parent scope
# ExternalProject_Get_Property(external_boost_header_only source_dir)
# set(BOOST_INCLUDE_DIR ${source_dir}/boost-1.64.0/ CACHE INTERNAL "Path to include folder for boost")
# include_directories(${BOOST_INCLUDE_DIR})


# #---------------------------------------------------
# # GSL: Guideline Support Library  
# #---------------------------------------------------
# ExternalProject_Add(
#     external_gsl
#     PREFIX ${CMAKE_BINARY_DIR}/external_projects/GSL
#     GIT_REPOSITORY https://github.com/Microsoft/GSL
#     GIT_TAG b01450878b39307df9abb702f02ce8c1d6c9ee30
#     TIMEOUT 5
#     #UPDATE_COMMAND ${GIT_EXECUTABLE} pull
#     CONFIGURE_COMMAND ""
#     BUILD_COMMAND ""
#     INSTALL_COMMAND ""
#     LOG_DOWNLOAD ON
# )
# # Expose required variable (DOCTEST_INCLUDE_DIR) to parent scope
# ExternalProject_Get_Property(external_gsl source_dir)
# set(GSL_INCLUDE_DIR ${source_dir}/include/ CACHE INTERNAL "Path to include folder for GSL")
# include_directories(${GSL_INCLUDE_DIR})

# #---------------------------------------------------
# # xtensor 
# #---------------------------------------------------
# ExternalProject_Add(
#     external_xtensor
#     PREFIX ${CMAKE_BINARY_DIR}/external_projects/xtensor
#     GIT_REPOSITORY https://github.com/QuantStack/xtensor
#     GIT_TAG 0.10.7
#     TIMEOUT 5
#     #UPDATE_COMMAND ${GIT_EXECUTABLE} pull
#     CONFIGURE_COMMAND ""
#     BUILD_COMMAND ""
#     INSTALL_COMMAND ""
#     LOG_DOWNLOAD ON
# )
# # Expose required variable (DOCTEST_INCLUDE_DIR) to parent scope
# ExternalProject_Get_Property(external_xtensor source_dir)
# set(XTENSOR_INCLUDE_DIR ${source_dir}/include/ CACHE INTERNAL "Path to include folder for xtensor")
# include_directories(${XTENSOR_INCLUDE_DIR})


# meta target for all to handle dependencies
add_custom_target(externl_headers)
# add_dependencies(externl_headers
#     # external_boost_header_only
#     # external_gsl 
#     # external_xtensor
# )







#-------------------------------------------------------------------------------------------------------------------
# enable `make test` in root dir
#-------------------------------------------------------------------------------------------------------------------
if(BUILD_TESTS)
    enable_testing()
endif()

#------------------------------------------------------------------------------------------------------------------
# src folder
#-------------------------------------------------------------------------------------------------------------------
add_subdirectory(src)





#------------------------------------------------------------------------------------------------------------------
# install
#-------------------------------------------------------------------------------------------------------------------
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)


install(DIRECTORY  ${${PROJECT_NAME}_INCLUDE_DIR}/nifty/meta
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/nifty)


set(${PROJECT_NAME}_CMAKECONFIG_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}" CACHE
    STRING "install path for ${PROJECT_NAME}Config.cmake")

configure_package_config_file(${PROJECT_NAME}Config.cmake.in
                              "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
                              INSTALL_DESTINATION ${${PROJECT_NAME}_CMAKECONFIG_INSTALL_DIR})


write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
                                 VERSION ${${PROJECT_NAME}_VERSION}
                                 COMPATIBILITY AnyNewerVersion)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
        DESTINATION ${${PROJECT_NAME}_CMAKECONFIG_INSTALL_DIR})
