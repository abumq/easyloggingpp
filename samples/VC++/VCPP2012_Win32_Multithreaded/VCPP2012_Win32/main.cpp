/**
 * This file is part of EasyLogging++ samples
 * Demonstration of VC++ thread
 * Base code taken from: http://msdn.microsoft.com/en-us/library/12a04hfd(v=vs.80).aspx
 * 
 * Revision: 1.0
 * @author mkhan3189
 */

#define _ELPP_STL_LOGGING

#include <iostream>
#include <windows.h>
#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

using namespace std;

volatile bool Sentinel = true;
int CriticalData = 0;

unsigned ThreadFunc1( void* pArguments ) {
   while (Sentinel)
      Sleep(0);   // volatile spin lock
   // CriticalData load guaranteed after every load of Sentinel
   LINFO << "ThreadFunc1 log - Critical Data = " << CriticalData;
   
   return 0;
} 

unsigned  ThreadFunc2( void* pArguments ) {
   Sleep(2000);
   CriticalData++;   // guaranteed to occur before write to Sentinel
   Sentinel = false; // exit critical section
    LDEBUG << "test";
   return 0;
}

int main() {
   HANDLE hThread1, hThread2; 
   DWORD retCode;

   hThread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&ThreadFunc1, NULL, 0, NULL);
   hThread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&ThreadFunc2, NULL, 0, NULL);

   if (hThread1 == NULL || hThread2 == NULL)       {
      LERROR << "CreateThread failed - Could not create thread";
      return 1;
   }

   retCode = WaitForSingleObject(hThread1,3000);

   CloseHandle(hThread1);
   CloseHandle(hThread2);

   if (retCode == WAIT_OBJECT_0 && CriticalData == 1 )
      LINFO << "Succeeded";
   else
      LERROR << "Failed";

   system("pause");
}