#
# Locate easylogging++ library
#
# This module defines:
# EASYLOGGINGPP_INCLUDE_DIR, directory path where to find
# 	easylogging++ directory with all necessary headers.
# 
# $EASYLOGGINGPP_ROOT is an environment variable that
# would correspond to the installation path.
#
# https://labs.muflihun.com
# https://muflihun.com
#

set(EASYLOGGINGPP_PATHS	${EASYLOGGINGPP_ROOT} $ENV{EASYLOGGINGPP_ROOT})	

find_path(EASYLOGGINGPP_INCLUDE_DIR 
	easylogging++.h 
	PATH_SUFFIXES include
	PATHS ${EASYLOGGINGPP_PATHS}
)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(EASYLOGGINGPP REQUIRED_VARS EASYLOGGINGPP_INCLUDE_DIR)
