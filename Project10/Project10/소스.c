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
	// ù��° ������ ����
	HANDLE hThread = NULL;
	DWORD dwThreadID = NULL;
	int firstThread = 0; // 0x44335832473439572
	hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadFunction, &firstThread, 0, (unsigned*)& dwThreadID);
	if (hThread == 0) Error("_beginthreadex Error\n");
	printf("������ �������� �ڵ� : %d\n", (int)hThread);
	printf("������ �������� ID : %d\n", dwThreadID);

	// �ι�° ������ ����
	HANDLE hThread2 = NULL;
	DWORD dwThreadID2 = NULL;
	int secondThread = 1;
	hThread2 = (HANDLE)_beginthreadex(NULL, 0, ThreadFunction, &secondThread, 0, (unsigned*)& dwThreadID2);
	if (hThread2 == 0) Error("_beginthreadex Error\n");
	printf("������ �������� �ڵ� : %d\n", (int)hThread2);
	printf("������ �������� ID : %d\n", dwThreadID2);

	// main �����尡 �����ϸ� ��Ŀ�����嵵 �����ϹǷ� ���� ����ϰ� �Ѵ�
	WaitForSingleObject(hThread, INFINITE);

	printf("main �Լ� ����!!\n");
	return 0;
}

unsigned int WINAPI ThreadFunction(void* arg)
{
	int id = *((int*)arg);

	while (1) {
		waiting[id] = 1;

		while (request != id) {	//�޶�
			while (waiting[1 - id] == 1) {	//��� ������ ����
				request = id;	//����
				printf("request is now %d\n", id);
			}

		}	//���ƾ� ���԰���

		printf("%d\n ", id);

		/*  CRITICAL SECTION  */

		waiting[id] = 0;	//��� ������ �� 

		/*  Remainder  */
	}

	printf("id=%d ������ ���� \n", GetCurrentThreadId());
	return 0;
}

void Error(const char* mes)
{
	printf("%s\n", mes);
	exit(0);
}
