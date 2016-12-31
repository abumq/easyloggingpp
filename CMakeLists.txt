cmake_minimum_required(VERSION 3.1)

project(Easyloggingpp CXX)

set(ELPP_MAJOR_VERSION "9")
set(ELPP_MINOR_VERSION "89")
set(ELPP_VERSION_STRING "${ELPP_MAJOR_VERSION}.${ELPP_MINOR_VERSION}")

set(ELPP_INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/include" CACHE PATH "The directory the headers are installed in")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

install(FILES src/easylogging++.h
    DESTINATION "${ELPP_INCLUDE_INSTALL_DIR}"
    COMPONENT dev)

export(PACKAGE ${PROJECT_NAME})
