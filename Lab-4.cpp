#include "pch.h"
#include <iostream>
#include "windows.h"
#include "random"
#include "ctime"
using namespace std;

HANDLE hth1, hth2;
long arr [10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

void thread_1()
{
	LONG rand_num;
	srand(time_t(NULL));
	while (TRUE)
	{
		Sleep(400);
		for (int i = 0; i < 10; i++)
		{
			rand_num = -150 + (rand() % 300);
			InterlockedExchange(&arr[i], rand_num);
		}
		Sleep(1000);
		for (int i = 0; i < 10; i++)
		{
			cout << arr[i] << " ";
		}
		cout << "\n";
	}
	}
}

void thread_2()
{
	while (TRUE)
	{
		for (int i = 0; i < 10; i++)
		{
			if (arr[i] > 0)
			{
				InterlockedExchange(&arr[i], 0);
			}
			
		}
	}
}


int main()
{
	DWORD idth1, idth2;

	hth1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) thread_1, NULL, 0, &idth1);
	hth2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_2, NULL, 0, &idth2);
	
	WaitForSingleObject(hth1, INFINITE);
	WaitForSingleObject(hth2, INFINITE);
	
	TerminateThread(hth1, 0); CloseHandle(hth1);
	TerminateThread(hth2, 0); CloseHandle(hth2);
	return 0;
}