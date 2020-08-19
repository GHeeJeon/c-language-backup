#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <process.h>


int waiting[2];

int request;

unsigned int WINAPI ThreadFunction(void* arg);
void Error(const char* mes);

int main()
{
	// 첫번째 쓰레드 설정
	HANDLE hThread = NULL;
	DWORD dwThreadID = NULL;
	int firstThread = 0; // 0x44335832473439572
	hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadFunction, &firstThread, 0, (unsigned*)& dwThreadID);
	if (hThread == 0) Error("_beginthreadex Error\n");
	printf("생성된 쓰레드의 핸들 : %d\n", (int)hThread);
	printf("생성된 쓰레드의 ID : %d\n", dwThreadID);

	// 두번째 쓰레드 설정
	HANDLE hThread2 = NULL;
	DWORD dwThreadID2 = NULL;
	int secondThread = 1;
	hThread2 = (HANDLE)_beginthreadex(NULL, 0, ThreadFunction, &secondThread, 0, (unsigned*)& dwThreadID2);
	if (hThread2 == 0) Error("_beginthreadex Error\n");
	printf("생성된 쓰레드의 핸들 : %d\n", (int)hThread2);
	printf("생성된 쓰레드의 ID : %d\n", dwThreadID2);

	// main 쓰레드가 종료하면 워커쓰레드도 종료하므로 무한 대기하게 한다
	WaitForSingleObject(hThread, INFINITE);

	printf("main 함수 종료!!\n");
	return 0;
}

unsigned int WINAPI ThreadFunction(void* arg)
{
	int id = *((int*)arg);

	while (1) {
		waiting[id] = 1;

		while (request != id) {	//달라
			while (waiting[1 - id] == 1) {	//상대 스레드 시작
				request = id;	//같아
				printf("request is now %d\n", id);
			}

		}	//같아야 진입가능

		printf("%d\n ", id);

		/*  CRITICAL SECTION  */

		waiting[id] = 0;	//상대 스레드 끝 

		/*  Remainder  */
	}

	printf("id=%d 쓰레드 종료 \n", GetCurrentThreadId());
	return 0;
}

void Error(const char* mes)
{
	printf("%s\n", mes);
	exit(0);
}
