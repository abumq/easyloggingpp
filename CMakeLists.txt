cmake_minimum_required(VERSION 2.8.7)

project(Easyloggingpp CXX)

macro(require_cpp11)
        if (${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} GREATER 3.0)
                # CMake 3.1 has built-in CXX standard checks.
                message("-- Setting C++11")
                set(CMAKE_CXX_STANDARD 11)
                set(CMAKE_CXX_STANDARD_REQUIRED on)
        else()
                if (CMAKE_CXX_COMPILER_ID MATCHES "GCC")
                    message ("-- GNU CXX (-std=c++11)")
                    list(APPEND CMAKE_CXX_FLAGS "-std=c++11")
                elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
                    message ("-- CLang CXX (-std=c++11)")
                    list(APPEND CMAKE_CXX_FLAGS "-std=c++11")
                else()
                    message ("-- Easylogging++ requires C++11. Your compiler does not support it.")
                endif()
        endif()
endmacro()

option(test "Build all tests" OFF)
option(build_static_lib "Build easyloggingpp as a static library" OFF)
option(build_shared_lib "Build easyloggingpp as a shared library" OFF)
option(lib_utc_datetime "Build library with UTC date/time logging" OFF)

set(ELPP_MAJOR_VERSION "9")
set(ELPP_MINOR_VERSION "96")
set(ELPP_PATCH_VERSION "7")
set(ELPP_VERSION_STRING "${ELPP_MAJOR_VERSION}.${ELPP_MINOR_VERSION}.${ELPP_PATCH_VERSION}")

include(GNUInstallDirs)

set(ELPP_INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_INCLUDEDIR}" CACHE PATH "The directory the headers are installed in")
set(ELPP_PKGCONFIG_INSTALL_DIR "${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig" CACHE PATH "Installation directory for pkgconfig (.pc) files")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

install(FILES
    src/easylogging++.h
    src/easylogging++.cc
    DESTINATION "${ELPP_INCLUDE_INSTALL_DIR}"
    COMPONENT dev)

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/cmake/easyloggingpp.pc.cmakein
    ${CMAKE_CURRENT_BINARY_DIR}/easyloggingpp.pc @ONLY)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/easyloggingpp.pc DESTINATION "${ELPP_PKGCONFIG_INSTALL_DIR}")

include(CheckIncludeFileCXX)
check_include_file_cxx("execinfo.h" HAVE_EXECINFO)
if (HAVE_EXECINFO)
	add_definitions(-DHAVE_EXECINFO)
endif()

if (build_shared_lib OR build_shared_lib)
        if (lib_utc_datetime)
                add_definitions(-DELPP_UTC_DATETIME)
        endif()

        require_cpp11()
endif()

if (build_static_lib)
        add_library(easyloggingpp_static STATIC src/easylogging++.cc)
        set_target_properties(easyloggingpp_static PROPERTIES
            OUTPUT_NAME easyloggingpp
            POSITION_INDEPENDENT_CODE ON)
        set_property(TARGET easyloggingpp_static PROPERTY POSITION_INDEPENDENT_CODE ON)

        install(TARGETS
            easyloggingpp_static
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
endif()
if (build_shared_lib)
        add_library(easyloggingpp_shared SHARED src/easylogging++.cc)
        set_target_properties(easyloggingpp_shared PROPERTIES
            OUTPUT_NAME easyloggingpp
            POSITION_INDEPENDENT_CODE ON
            SOVERSION "${ELPP_MAJOR_VERSION}"
            VERSION "${ELPP_MAJOR_VERSION}.${ELPP_MINOR_VERSION}.${ELPP_PATCH_VERSION}")

        install(TARGETS
            easyloggingpp_shared
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
endif()

export(PACKAGE ${PROJECT_NAME})


########################################## Unit Testing ###################################
if (test)
    # We need C++11
    require_cpp11()
    set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

    find_package (gtest REQUIRED)

    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

    enable_testing()

    if (EMSCRIPTEN)
        set(CMAKE_EXE_LINKER_FLAGS "-O2 -s TOTAL_MEMORY=134217728")
    endif()

    add_executable(easyloggingpp-unit-tests
        src/easylogging++.cc
        test/main.cc
    )

    target_compile_definitions(easyloggingpp-unit-tests PUBLIC
        ELPP_FEATURE_ALL
        ELPP_LOGGING_FLAGS_FROM_ARG
        ELPP_NO_DEFAULT_LOG_FILE
        ELPP_FRESH_LOG_FILE
    )

    # Standard linking to gtest stuff.
    target_link_libraries(easyloggingpp-unit-tests gtest gtest_main)

    add_test(NAME easyloggingppUnitTests COMMAND easyloggingpp-unit-tests -v)
endif()
