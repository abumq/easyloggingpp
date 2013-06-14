#!/bin/bash

## Bash script that copies easylogging++.h to samples where needed

## samples
cp easylogging++.h samples/Qt/basic/
cp easylogging++.h samples/Qt/building-blocks/engine/
cp easylogging++.h samples/STL/
cp easylogging++.h samples/Android/NDKEasyLoggingPP/jni/
cp easylogging++.h samples/Qt/multiple-libs/lib1/
cp easylogging++.h samples/Qt/multiple-libs/lib2/
cp easylogging++.h samples/Qt/multiple-libs/libtester/
cp easylogging++.h samples/VC++/VCPP2012_Win32_Multithreaded/VCPP2012_Win32/
cp easylogging++.h samples/wxWidgets/

## tools
cp easylogging++.h tools/LogViewer/
cp easylogging++.h tools/ConfigurationBuilder/
