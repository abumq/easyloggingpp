/**
 * EasyLogging++ NDK sample for Android app
 *
 * The original log file path we used to do initial testing was:
 *     /data/data/com.samples.ndkeasyloggingpp/logs/
 *
 * This might have changed in easylogging++.h when you see it (we copy files across
 * with every new release)
 *
 * @author mkhan3189
 */

#include <string.h>
#include <jni.h>

#define _DEBUG  // We are debugging! Otherwise how would we log debug logs??

#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

extern "C" {
    JNIEXPORT jstring JNICALL Java_com_samples_ndkeasyloggingpp_MainActivity_messageFromNative(JNIEnv * env, jobject obj);
};

JNIEXPORT jstring JNICALL Java_com_samples_ndkeasyloggingpp_MainActivity_messageFromNative (JNIEnv* env, jobject jObj)
{

    LDEBUG << "Calling native code";

    LINFO << "This is info log";

    LTRACE << "This is trace";

    LINFO << "This is info log2 ";

    return env->NewStringUTF("Hello from native code!");

}

