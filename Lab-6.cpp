#include "pch.h"
#include <iostream>
#include "windows.h"
#include "ctime"
#include "iomanip"

using namespace std;

long arr[7];
HANDLE hsemaphore;
long rand_num;

void thread_1()
{
	srand(time_t(NULL));
	for (int i = 0; i < 7; i++)
		{		
			WaitForSingleObject(hsemaphore, INFINITE);
			Sleep(100);
			rand_num = rand() % 501;
			arr[i] = rand_num;
			cout << arr[i] << " -> ";
			ReleaseSemaphore(hsemaphore, 1, NULL);
		}
		
}

void thread_2()
{	
	Sleep(10);
	for (int i = 0; i < 7; i++)
		{
			WaitForSingleObject(hsemaphore, INFINITE);
			if (arr[i] % 2 == 0) arr[i] = 0;
			cout << arr[i] << "; ";
			ReleaseSemaphore(hsemaphore, 1, NULL);
		}
}

int main()
{
	hsemaphore = CreateSemaphore(NULL, 1, 1, "MySemaphore");
	HANDLE hth1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_1, NULL, 0, NULL);
	HANDLE hth2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_2, NULL, 0, NULL);

	cin.ignore();
	cin.get();

	CloseHandle(hsemaphore);
	CloseHandle(hth1);
	CloseHandle(hth2);
	return 0;
}