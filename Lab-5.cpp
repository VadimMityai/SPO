#include "pch.h"
#include <iostream>
#include "Windows.h"
#include "ctime"
#include "iomanip"

using namespace std;

long arr[10];

void thread_1()
{	
	srand(time_t(NULL));
	
	for (int k = 0; k < 3; k++)
	{
		
		LONG num;
		HANDLE hMutex_1 = OpenMutex(SYNCHRONIZE, FALSE, "MyMutex");
		WaitForSingleObject(hMutex_1, INFINITE);
		for (int i = 0; i < 10; i++)
		{
			num = rand() % 10 - 5;
			InterlockedExchange(&arr[i], num);
			cout << setw(6) << arr[i];
		}
		cout << endl;
		Sleep(200);
		ReleaseMutex(hMutex_1);
		CloseHandle(hMutex_1);		
	}	
}

void thread_2()
{
	Sleep(50);
	long rand_num;
	for (int p = 0; p < 3; p++)
	{
		HANDLE hMutex_2 = OpenMutex(SYNCHRONIZE, FALSE, "MyMutex");
		WaitForSingleObject(hMutex_2, INFINITE);
		for (int i = 0; i < 10; i++)
		{
			if (arr[i] < 0)
			{
				rand_num = pow(arr[i], 2);
				InterlockedExchange(&arr[i], rand_num);
			}
			cout << setw(6) << arr[i];
		}
		cout << "\n \n";
		Sleep(200);
		ReleaseMutex(hMutex_2);
		CloseHandle(hMutex_2);
	}	
}

int main()
{
	HANDLE hMutex = CreateMutex(NULL, FALSE, "MyMutex");
	
	HANDLE hth1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_1, NULL, 0, NULL);

	HANDLE hth2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_2, NULL, 0, NULL);

	cin.get();

	CloseHandle(hMutex);
	CloseHandle(hth1);
	CloseHandle(hth2);
	return 0;
}