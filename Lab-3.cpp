#include "pch.h"
#include <iostream>
#include <windows.h>
#include <iomanip>
#include <stdlib.h>
using namespace std;

HANDLE hth1, hth2, hth3;
int i_1 = 0;
int i_2 = 0;
int i_3 = 0;

void thread_1()
{
	Sleep(10);
	cout << "Thread 1 is working... \n";
	while (TRUE)
	{
		i_1 += 1;
		Sleep(10);
		//cout << i_1 << endl;
	}
}

void thread_2()
{
	Sleep(10);
	cout << "Thread 2 is working... \n";
	while (TRUE)
	{
		i_2 += 1;
		Sleep(50);
		//cout << i_2 << endl;
	}
}

void thread_3()
{
	Sleep(10);
	cout << "Thread 3 is working... \n";
	while (TRUE)
	{
		i_3 += 1;
		Sleep(100);
		//cout << i_3 << endl;
	}
}

int main()
{
	DWORD idth1, idth2, idth3;
	char answer = 'w';

	hth1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_1, NULL, 0, &idth1);
	hth2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_2, NULL, 0, &idth2);
	hth3 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_3, NULL, 0, &idth3);

	while (answer != 'q')
	{
		cout << "'d' -> delete min thread; 'q' -> exit: \n";
		cin >> answer;
		if (answer == 'd')
		{
			cout << "First thread has: " << i_1 << endl;
			cout << "Second thread has: " << i_2 << endl;
			cout << "Third thread has: " << i_3 << endl;

			int min_i = min(min(i_1, i_2), i_3);
			if (min_i == i_1)
			{
				TerminateThread(hth1, 0);
				cout << "Terminated 1_st thread \n";
			}
			else if (min_i == i_2)
			{
				TerminateThread(hth2, 0);
				cout << "Terminated 2_nd thread \n";
			}
			else
			{
				TerminateThread(hth3, 0);
				cout << "Terminated 3_d thread \n";
			}
			break;
		}
	}

	TerminateThread(hth1, 0); CloseHandle(hth1);
	TerminateThread(hth2, 0); CloseHandle(hth2);
	TerminateThread(hth3, 0); CloseHandle(hth3);

	return 0;
}