#include <windows.h>
#include <iostream>
#include "lab3.h"

using namespace std;

#define THREAD_COUNT 11
#define SEMAPHORE_COUNT 4

DWORD ThreadID;
HANDLE hThread[THREAD_COUNT];
HANDLE hSemaphore[SEMAPHORE_COUNT];
HANDLE hMutex;

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



DWORD WINAPI thread_a(LPVOID);
DWORD WINAPI thread_b(LPVOID);
DWORD WINAPI thread_c(LPVOID);
DWORD WINAPI thread_d(LPVOID);
DWORD WINAPI thread_e(LPVOID);
DWORD WINAPI thread_f(LPVOID);
DWORD WINAPI thread_g(LPVOID);
DWORD WINAPI thread_h(LPVOID);
DWORD WINAPI thread_i(LPVOID);
DWORD WINAPI thread_k(LPVOID);
DWORD WINAPI thread_m(LPVOID);
DWORD WINAPI thread_e_sem(LPVOID);
DWORD WINAPI thread_f_sem(LPVOID);
DWORD WINAPI thread_g_sem(LPVOID);
DWORD WINAPI thread_h_sem(LPVOID);


DWORD WINAPI thread_a(LPVOID lpParam)
{
	//T0------>
		// start e
	hThread[4] = CreateThread(NULL, 0, thread_e, NULL, 0, &ThreadID);
	if (hThread[4] == NULL) {
		return GetLastError();
	}
	// start c
	hThread[2] = CreateThread(NULL, 0, thread_c, NULL, 0, &ThreadID);
	if (hThread[2] == NULL) {
		return GetLastError();
	}
	// start d
	hThread[3] = CreateThread(NULL, 0, thread_d, NULL, 0, &ThreadID);
	if (hThread[3] == NULL) {
		return GetLastError();
	}

	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(hMutex, INFINITE);
		cout << "a" << flush;
		computation();
		ReleaseMutex(hMutex);
	}

	// wait e
	WaitForSingleObject(hThread[4], INFINITE);
	// wait c
	WaitForSingleObject(hThread[2], INFINITE);
	// wait d
	WaitForSingleObject(hThread[3], INFINITE);
	// close e
	CloseHandle(hThread[4]);
	// close c
	CloseHandle(hThread[2]);
	// close d
	CloseHandle(hThread[3]);

	//<------T0

	//T1------>
		// start b
	hThread[1] = CreateThread(NULL, 0, thread_b, NULL, 0, &ThreadID);
	if (hThread[1] == NULL) {
		return GetLastError();
	}
	// start c
	hThread[2] = CreateThread(NULL, 0, thread_c, NULL, 0, &ThreadID);
	if (hThread[2] == NULL) {
		return GetLastError();
	}
	// start d
	hThread[3] = CreateThread(NULL, 0, thread_d, NULL, 0, &ThreadID);
	if (hThread[3] == NULL) {
		return GetLastError();
	}
	// start e
	hThread[4] = CreateThread(NULL, 0, thread_e, NULL, 0, &ThreadID);
	if (hThread[4] == NULL) {
		return GetLastError();
	}

	// wait b
	WaitForSingleObject(hThread[1], INFINITE);
	// wait c
	WaitForSingleObject(hThread[2], INFINITE);
	// wait d
	WaitForSingleObject(hThread[3], INFINITE);
	// wait e
	WaitForSingleObject(hThread[4], INFINITE);
	// close b
	CloseHandle(hThread[1]);
	// close c
	CloseHandle(hThread[2]);
	// close d
	CloseHandle(hThread[3]);
	// close e
	CloseHandle(hThread[4]);

	//<------T1

	//T2------>
		// start e
	hThread[4] = CreateThread(NULL, 0, thread_e, NULL, 0, &ThreadID);
	if (hThread[4] == NULL) {
		return GetLastError();
	}
	// start d
	hThread[3] = CreateThread(NULL, 0, thread_d, NULL, 0, &ThreadID);
	if (hThread[3] == NULL) {
		return GetLastError();
	}

	// start g
	hThread[6] = CreateThread(NULL, 0, thread_g, NULL, 0, &ThreadID);
	if (hThread[6] == NULL) {
		return GetLastError();
	}

	// start h
	hThread[7] = CreateThread(NULL, 0, thread_h, NULL, 0, &ThreadID);
	if (hThread[7] == NULL) {
		return GetLastError();
	}

	// wait e
	WaitForSingleObject(hThread[4], INFINITE);
	// wait d
	WaitForSingleObject(hThread[3], INFINITE);
	// wait g
	WaitForSingleObject(hThread[6], INFINITE);
	// wait h
	WaitForSingleObject(hThread[7], INFINITE);

	// close G
	CloseHandle(hThread[4]);
	// close g
	CloseHandle(hThread[6]);
	// close h
	CloseHandle(hThread[7]);
	// close d
	CloseHandle(hThread[3]);

	//<------T2

	//T3------>

		// start e_sem
	hThread[4] = CreateThread(NULL, 0, thread_e_sem, NULL, 0, &ThreadID);
	if (hThread[4] == NULL) {
		return GetLastError();
	}
	// start f_sem
	hThread[5] = CreateThread(NULL, 0, thread_f_sem, NULL, 0, &ThreadID);
	if (hThread[5] == NULL) {
		return GetLastError();
	}
	// start g_sem
	hThread[6] = CreateThread(NULL, 0, thread_g_sem, NULL, 0, &ThreadID);
	if (hThread[6] == NULL) {
		return GetLastError();
	}
	// start h_sem
	hThread[7] = CreateThread(NULL, 0, thread_h_sem, NULL, 0, &ThreadID);
	if (hThread[7] == NULL) {
		return GetLastError();
	}

	// wait e_sem
	WaitForSingleObject(hThread[4], INFINITE);
	// wait f_sem
	WaitForSingleObject(hThread[5], INFINITE);
	// wait g_sem
	WaitForSingleObject(hThread[6], INFINITE);
	// wait h_sem
	WaitForSingleObject(hThread[7], INFINITE);

	// close e_sem
	CloseHandle(hThread[4]);
	// close f_sem
	CloseHandle(hThread[5]);
	// close g_sem
	CloseHandle(hThread[6]);
	// close h_sem
	CloseHandle(hThread[7]);

	//<------T3

	//T4------>

		// start h 
	hThread[7] = CreateThread(NULL, 0, thread_h, NULL, 0, &ThreadID);
	if (hThread[7] == NULL) {
		return GetLastError();
	}
	// start i
	hThread[8] = CreateThread(NULL, 0, thread_i, NULL, 0, &ThreadID);
	if (hThread[8] == NULL) {
		return GetLastError();
	}
	// start k 
	hThread[9] = CreateThread(NULL, 0, thread_k, NULL, 0, &ThreadID);
	if (hThread[9] == NULL) {
		return GetLastError();
	}

	// wait h 
	WaitForSingleObject(hThread[7], INFINITE);
	// wait i 
	WaitForSingleObject(hThread[8], INFINITE);
	// wait k 
	WaitForSingleObject(hThread[9], INFINITE);

	// close h
	CloseHandle(hThread[7]);
	// close i
	CloseHandle(hThread[8]);
	// close k
	CloseHandle(hThread[9]);

	//<------T4

	//T5------>
		// start m 
	hThread[10] = CreateThread(NULL, 0, thread_m, NULL, 0, &ThreadID);
	if (hThread[10] == NULL) {
		return GetLastError();
	}

	// wait m 
	WaitForSingleObject(hThread[10], INFINITE);

	// close m
	CloseHandle(hThread[10]);


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

	return 0;
}

DWORD WINAPI thread_d(LPVOID lpParam)
{
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(hMutex, INFINITE);
		cout << "d" << flush;
		computation();
		ReleaseMutex(hMutex);
	}

	return 0;
}

DWORD WINAPI thread_e(LPVOID lpParam)
{
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(hMutex, INFINITE);
		cout << "e" << flush;
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
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(hMutex, INFINITE);
		cout << "g" << flush;
		computation();
		ReleaseMutex(hMutex);
	}

	return 0;
}

DWORD WINAPI thread_f(LPVOID lpParam)
{
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(hMutex, INFINITE);
		cout << "f" << flush;
		computation();
		ReleaseMutex(hMutex);
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

DWORD WINAPI thread_e_sem(LPVOID lpParam)
{
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(hSemaphore[0], INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		cout << "e" << flush;
		computation();
		ReleaseMutex(hMutex);
		ReleaseSemaphore(hSemaphore[1], 1, NULL);
	}

	return 0;
}

DWORD WINAPI thread_f_sem(LPVOID lpParam)
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

DWORD WINAPI thread_g_sem(LPVOID lpParam)
{
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

DWORD WINAPI thread_h_sem(LPVOID lpParam)
{
	for (int i = 0; i < 3; i++) {
		WaitForSingleObject(hSemaphore[3], INFINITE);
		WaitForSingleObject(hMutex, INFINITE);
		cout << "h" << flush;
		computation();
		ReleaseMutex(hMutex);
		ReleaseSemaphore(hSemaphore[0], 1, NULL);
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

	for (int i = 0; i < SEMAPHORE_COUNT; i++) {
		hSemaphore[i] = CreateSemaphore(NULL, i == 0 ? 1 : 0, 1, NULL);
		if (hSemaphore[i] == NULL) {
			cout << "CreateSemaphore error: " << GetLastError();
			return 1;
		}
	}

	// start A
	hThread[0] = CreateThread(NULL, 0, thread_a, NULL, 0, &ThreadID);
	if (hThread[0] == NULL) {
		return GetLastError();
	}
	// wait A
	WaitForSingleObject(hThread[0], INFINITE);
	// close A
	CloseHandle(hThread[0]);

	CloseHandle(hMutex);

	for (int i = 0; i < SEMAPHORE_COUNT; i++) {
		CloseHandle(hSemaphore[i]);
	}

	return 0;
}
