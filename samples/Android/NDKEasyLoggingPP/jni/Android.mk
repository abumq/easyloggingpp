LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := libEasyLoggingTest
LOCAL_SRC_FILES := hello.cpp \
                   easylogging++.h

include $(BUILD_SHARED_LIBRARY)