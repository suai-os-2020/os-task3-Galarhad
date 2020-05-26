#include <windows.h>
#include <iostream>
#include "lab3.h"

using namespace std;

#define THREAD_COUNT 11
#define SEMAPHORE_COUNT 4

DWORD ThreadID;
HANDLE hThread[THREAD_COUNT];
HANDLE hSemaphore[SEMAPHORE_COUNT],wait,up;
HANDLE hMutex;
boolean d0,c0,h0,h1;

unsigned int lab3_thread_graph_id()
{
    return 4;
}

const char* lab3_unsynchronized_threads()
{
    return "bcde";
}

const char* lab3_sequential_threads()
{
    return "efgh";
}



DWORD WINAPI thread_a(LPVOID);//0
DWORD WINAPI thread_b(LPVOID);//1
DWORD WINAPI thread_c(LPVOID);//2
DWORD WINAPI thread_d(LPVOID);//3
DWORD WINAPI thread_e(LPVOID);//4
DWORD WINAPI thread_f(LPVOID);//5
DWORD WINAPI thread_g(LPVOID);//6
DWORD WINAPI thread_h(LPVOID);//7
DWORD WINAPI thread_i(LPVOID);//8
DWORD WINAPI thread_k(LPVOID);//9
DWORD WINAPI thread_m(LPVOID);//10
DWORD WINAPI thread_e_sem(LPVOID);
DWORD WINAPI thread_f_sem(LPVOID);
DWORD WINAPI thread_g_sem(LPVOID);
DWORD WINAPI thread_h_sem(LPVOID);


DWORD WINAPI thread_e(LPVOID lpParam)
{
    //t0--->
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hMutex, INFINITE);
        cout << "e" << flush;
        computation();
        ReleaseMutex(hMutex);
    }

    hThread[0] = CreateThread(NULL, 0, thread_a, NULL, 0, &ThreadID);
    if (hThread[0] == NULL) {
        return GetLastError();
    }
    hThread[2] = CreateThread(NULL, 0, thread_c, NULL, 0, &ThreadID);
    if (hThread[2] == NULL) {
        return GetLastError();
    }
    hThread[3] = CreateThread(NULL, 0, thread_d, NULL, 0, &ThreadID);
    if (hThread[3] == NULL) {
        return GetLastError();
    }
    // wait a
    WaitForSingleObject(hThread[0], INFINITE);
    //wait c,d
    WaitForSingleObject(wait, INFINITE);
    WaitForSingleObject(wait, INFINITE);
    //<------T0

    //T1------>
    // wakeUp C,D
    ReleaseSemaphore(up, 1, NULL);
    ReleaseSemaphore(up, 1, NULL);

    hThread[1] = CreateThread(NULL, 0, thread_b, NULL, 0, &ThreadID);
    if (hThread[1] == NULL) {
        return GetLastError();
    }
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hMutex, INFINITE);
        cout << "e" << flush;
        computation();
        ReleaseMutex(hMutex);
    }
    // wait b
    WaitForSingleObject(hThread[1], INFINITE);
    // wait c
    WaitForSingleObject(hThread[2], INFINITE);
    //wait d
    WaitForSingleObject(wait, INFINITE);
    //T1<---

    //T2--->
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hMutex, INFINITE);
        cout << "e" << flush;
        computation();
        ReleaseMutex(hMutex);
    }
    // wakeUp d
    ReleaseSemaphore(up, 1, NULL);
    hThread[6] = CreateThread(NULL, 0, thread_g, NULL, 0, &ThreadID);
    if (hThread[6] == NULL) {
        return GetLastError();
    }
    hThread[7] = CreateThread(NULL, 0, thread_h, NULL, 0, &ThreadID);
    if (hThread[7] == NULL) {
        return GetLastError();
    }
    // wait c
    WaitForSingleObject(hThread[3], INFINITE);
    //wait g,h
    WaitForSingleObject(wait, INFINITE);
    WaitForSingleObject(wait, INFINITE);
    //T2<---

    //T3--->
    hThread[5] = CreateThread(NULL, 0, thread_f, NULL, 0, &ThreadID);
    if (hThread[5] == NULL) {
        return GetLastError();
    }
    // wakeUp g,h
    ReleaseSemaphore(up, 1, NULL);
    ReleaseSemaphore(up, 1, NULL);
    // start e
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hSemaphore[0], INFINITE);
        WaitForSingleObject(hMutex, INFINITE);
        cout << "e" << flush;
        computation();
        ReleaseMutex(hMutex);
        ReleaseSemaphore(hSemaphore[1], 1, NULL);
    }



    // wait c
    WaitForSingleObject(hThread[6], INFINITE);
    WaitForSingleObject(hThread[5], INFINITE);
    //wait h
    WaitForSingleObject(wait, INFINITE);
    //T3<---

    //T4--->
    hThread[8] = CreateThread(NULL, 0, thread_i, NULL, 0, &ThreadID);
    if (hThread[8] == NULL) {
        return GetLastError();
    }
    hThread[9] = CreateThread(NULL, 0, thread_k, NULL, 0, &ThreadID);
    if (hThread[9] == NULL) {
        return GetLastError();
    }
    // wakeUp h
    ReleaseSemaphore(up, 1, NULL);
    // wait h,i,k
    WaitForSingleObject(hThread[8], INFINITE);
    WaitForSingleObject(hThread[9], INFINITE);
    WaitForSingleObject(hThread[7], INFINITE);
    //T4<---


    //T5--->
    hThread[10] = CreateThread(NULL, 0, thread_m, NULL, 0, &ThreadID);
    if (hThread[10] == NULL) {
        return GetLastError();
    }
    WaitForSingleObject(hThread[10], INFINITE);
    //T5<---


    return 0;
}

DWORD WINAPI thread_a(LPVOID lpParam)
{
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hMutex, INFINITE);
        cout << "a" << flush;
        computation();
        ReleaseMutex(hMutex);
    }

    return 0;
}

DWORD WINAPI thread_b(LPVOID lpParam)
{
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hMutex, INFINITE);
        cout << "b" << flush;
        computation();
        ReleaseMutex(hMutex);
    }

    return 0;
}

DWORD WINAPI thread_c(LPVOID lpParam)
{
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hMutex, INFINITE);
        cout << "c" << flush;
        computation();
        ReleaseMutex(hMutex);
    }
    ReleaseSemaphore(wait, 1, NULL);
    WaitForSingleObject(up, INFINITE);
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hMutex, INFINITE);
        cout << "c" << flush;
        computation();
        ReleaseMutex(hMutex);
    }

    return 0;
}

DWORD WINAPI thread_d(LPVOID lpParam)
{

    //t0
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hMutex, INFINITE);
        cout << "d" << flush;
        computation();
        ReleaseMutex(hMutex);
    }
    ReleaseSemaphore(wait, 1, NULL);
    WaitForSingleObject(up, INFINITE);
    //t1
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hMutex, INFINITE);
        cout << "d" << flush;
        computation();
        ReleaseMutex(hMutex);
    }
    ReleaseSemaphore(wait, 1, NULL);
    WaitForSingleObject(up, INFINITE);
    //t2
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hMutex, INFINITE);
        cout << "d" << flush;
        computation();
        ReleaseMutex(hMutex);
    }
    return 0;
}



DWORD WINAPI thread_i(LPVOID lpParam)
{
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hMutex, INFINITE);
        cout << "i" << flush;
        computation();
        ReleaseMutex(hMutex);
    }

    return 0;
}


DWORD WINAPI thread_h(LPVOID lpParam)
{
    //t2
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hMutex, INFINITE);
        cout << "h" << flush;
        computation();
        ReleaseMutex(hMutex);
    }
    ReleaseSemaphore(wait, 1, NULL);
    WaitForSingleObject(up, INFINITE);
    //t3
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hSemaphore[3], INFINITE);
        WaitForSingleObject(hMutex, INFINITE);
        cout << "h" << flush;
        computation();
        ReleaseMutex(hMutex);
        ReleaseSemaphore(hSemaphore[0], 1, NULL);
    }
    ReleaseSemaphore(wait, 1, NULL);
    WaitForSingleObject(up, INFINITE);
    //t4
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hMutex, INFINITE);
        cout << "h" << flush;
        computation();
        ReleaseMutex(hMutex);
    }


    return 0;
}

DWORD WINAPI thread_g(LPVOID lpParam)
{
    //t2
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hMutex, INFINITE);
        cout << "g" << flush;
        computation();
        ReleaseMutex(hMutex);
    }
    ReleaseSemaphore(wait, 1, NULL);
    WaitForSingleObject(up, INFINITE);
    //t3
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hSemaphore[2], INFINITE);
        WaitForSingleObject(hMutex, INFINITE);
        cout << "g" << flush;
        computation();
        ReleaseMutex(hMutex);
        ReleaseSemaphore(hSemaphore[3], 1, NULL);
    }

    return 0;
}

DWORD WINAPI thread_f(LPVOID lpParam)
{
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hSemaphore[1], INFINITE);
        WaitForSingleObject(hMutex, INFINITE);
        cout << "f" << flush;
        computation();
        ReleaseMutex(hMutex);
        ReleaseSemaphore(hSemaphore[2], 1, NULL);
    }

    return 0;
}

DWORD WINAPI thread_k(LPVOID lpParam)
{
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hMutex, INFINITE);
        cout << "k" << flush;
        computation();
        ReleaseMutex(hMutex);
    }

    return 0;
}

DWORD WINAPI thread_m(LPVOID lpParam)
{
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hMutex, INFINITE);
        cout << "m" << flush;
        computation();
        ReleaseMutex(hMutex);
    }

    return 0;
}

DWORD WINAPI thread_n(LPVOID lpParam)
{
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(hMutex, INFINITE);
        cout << "n" << flush;
        computation();
        ReleaseMutex(hMutex);
    }

    return 0;
}



int lab3_init()
{
    hMutex = CreateMutex(NULL, 0, NULL);
    if (hMutex == NULL) {
        cout << "CreateMutex error: " << GetLastError();
        return 1;
    }

    wait = CreateSemaphore(NULL, 0, 3, NULL);
    up = CreateSemaphore(NULL, 0, 3, NULL);

    for (int i = 0; i < SEMAPHORE_COUNT; i++) {
        hSemaphore[i] = CreateSemaphore(NULL, i == 0 ? 1 : 0, 1, NULL);
        if (hSemaphore[i] == NULL) {
            cout << "CreateSemaphore error: " << GetLastError();
            return 1;
        }
    }

    // start e
    hThread[4] = CreateThread(NULL, 0, thread_e, NULL, 0, &ThreadID);
    if (hThread[4] == NULL) {
        return GetLastError();
    }
    // wait A
    WaitForSingleObject(hThread[4], INFINITE);
    // close A
    for (int i = 0; i < THREAD_COUNT; ++i)
        CloseHandle(hThread[i]);

    CloseHandle(hMutex);

    for (int i = 0; i < SEMAPHORE_COUNT; i++) {
        CloseHandle(hSemaphore[i]);
    }

    return 0;
}
