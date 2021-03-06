/* Contact.c */
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Contact.h"
#include "Menu.h"

CONTACT* Initialize(int totalCnt)
{
	CONTACT *p = malloc(sizeof(CONTACT) * totalCnt);
	if (p != NULL)
		memset(p, 0, sizeof(CONTACT) * totalCnt);
	return p;
}

int AddContactInfo(CONTACT *contacts, int maxCnt, int *pCurCnt)
{
	//char name[MAX_STR];
	CONTACT *p = NULL;
	int ring;

	if (maxCnt == *pCurCnt)
		return 0;

	p = &contacts[*pCurCnt];


	printf("\n이    름 : ");
	fgets(p->name, MAX_STR, stdin);
	p->name[strlen(p->name) - 1] = '\0';  // 줄바꿈 문자 제거
	for (int i = 0; i < *pCurCnt; i++) {
		if (_strcmpi(contacts[i].name, p->name) == 0) {
			printf("이미 저장된 이름입니다. 동명이인일시 구별가능한 표식을 남겨주세요.");
			memset(&contacts[*pCurCnt], 0, sizeof(CONTACT));
			return *pCurCnt;
		}
	}


	while (1) {
		int flag = 0;
		printf("전화번호 : ");
		fgets(p->phone, MAX_STR, stdin);
		p->phone[strlen(p->phone) - 1] = '\0'; // 줄바꿈 문자 제거
		//
		for (int i = 0; i < strlen(p->phone); i++) {
			if ('0' <= p->phone[i] && p->phone[i] <= '9')
				flag++;
		}
		if (flag == strlen(p->phone))
			break;
		else {
			printf("숫자만 입력해주세요.\n");
			continue;
		}
			
	}

	do {
		printf("[1.전화벨 2.피아노 3.마림바 4.하프] 벨소리 선택 : ");
		scanf("%d", &ring);
		CLEAR_INPUT();
	} while (ring < 0 || ring > 4);
	p->ring = ring - 1;
	printf("연락처가 추가되었습니다.\n");
	(*pCurCnt)++;
	system("cls");
	return *pCurCnt;
}

void ListByName(CONTACT *contacts, int cnt)
{
	if (cnt == 0)
	{
		printf("출력할 내용이 없습니다.\n");
		return;
	}
	qsort(contacts, cnt, sizeof(CONTACT), CompareByName);
	PrintAllContacts(contacts, cnt);
}

void PrintAllContacts(const CONTACT *contacts, int cnt)
{
	int i;
	const char* ringtones[] = {
		"전화벨", "피아노", "마림바", "하프"
	};

	printf("\n==================================\n");
	printf(" 이름        전화번호     벨소리\n");
	printf("==================================\n");
	for (i = 0; i < cnt; i++)
	{
		printf("%-10s %-14s %s\n", contacts[i].name, contacts[i].phone,
			ringtones[contacts[i].ring]);
	}
	printf("==================================\n");
}

int CompareByName(const void* e1, const void* e2)
{
	const CONTACT *p1 = (const CONTACT*)e1;
	const CONTACT *p2 = (const CONTACT*)e2;
	return strcmp(p1->name, p2->name);
}

CONTACT* ExpandContacts(CONTACT *contacts, int *pMaxCnt)
{
	CONTACT *temp = realloc(contacts, sizeof(CONTACT)*(*pMaxCnt) * 2);
	if (temp == NULL)
		return NULL;
	*pMaxCnt = *pMaxCnt * 2;
	return temp;
}

void FindContact(CONTACT* contacts, int* pCurCnt)
{
	char name[MAX_STR];
	CONTACT* p = NULL;
	int i, j;
	int findMenu = 0;
	int ring;

	printf("찾을 이름 : ");
	fgets(name, MAX_STR, stdin);
	name[strlen(name) - 1] = '\0';
	for (i = 0; i < *pCurCnt; i++) {
		if (_strcmpi(contacts[i].name, name) == 0) {
			p = &contacts[i];
			break;
		}
	}
	if (p == NULL)
	{
		printf("연락처를 찾을 수 없습니다,\n");
		return;
	}
	printf("%-10s %-14s \n", contacts[i].name, contacts[i].phone);
	while (1)
	{
		findMenu = SelectFindMenu();
		if (findMenu == PREVIOUS_MENU)
			break;
		switch (findMenu)
		{
		case MODIFY_CONTACT:
			printf("\n이	름 : ");
			fgets(p->name, MAX_STR, stdin);
			p->name[strlen(p->name) - 1] = '\0';
			printf("전화번호 : ");
			fgets(p->phone, MAX_STR, stdin);
			p->phone[strlen(p->phone) - 1] = '\0';
			do {
				printf("[1.전화벨 2.피아노 3.마림바 4.하프] 벨소리 선택 : ");
				scanf("%d", &ring);
				CLEAR_INPUT();
			} while (ring < 0 || ring > 4);
			p->ring = ring - 1;
			printf("연락처를 수정했습니다.\n");
			break;
		case DELETE_CONTACT:
			for (j = i + 1; j < *pCurCnt; j++) {
				contacts[j - 1] = contacts[j];
			}
			memset(&contacts[j], 0, sizeof(CONTACT));
			(*pCurCnt)--;
			printf("연락처를 삭제했습니다.\n");
			break;
		}
		break;
	}
}
void PhoneContact(CONTACT* contacts, int* pCurCnt)
{
	char phone[MAX_STR];
	CONTACT* p = NULL;
	int i, j;
	int findMenu = 0;
	int ring;

	printf("찾을 전화번호 : ");
	fgets(phone, MAX_STR, stdin);
	phone[strlen(phone) - 1] = '\0';
	for (i = 0; i < *pCurCnt; i++) {
		if (_strcmpi(contacts[i].phone, phone) == 0) {
			p = &contacts[i];
			break;
		}
	}
	if (p == NULL)
	{
		printf("연락처를 찾을 수 없습니다,\n");
		return;
	}
	printf("%-10s %-14s \n", contacts[i].name, contacts[i].phone);
	while (1)
	{
		findMenu = SelectFindMenu();
		if (findMenu == PREVIOUS_MENU)
			break;
		switch (findMenu)
		{
		case MODIFY_CONTACT:
			printf("\n이	름 : ");
			fgets(p->name, MAX_STR, stdin);
			p->name[strlen(p->name) - 1] = '\0';
			printf("전화번호 : ");
			fgets(p->phone, MAX_STR, stdin);
			p->phone[strlen(p->phone) - 1] = '\0';
			do {
				printf("[1.전화벨 2.피아노 3.마림바 4.하프] 벨소리 선택 : ");
				scanf("%d", &ring);
				CLEAR_INPUT();
			} while (ring < 0 || ring > 4);
			p->ring = ring - 1;

			printf("연락처를 수정했습니다.\n");
			break;
		case DELETE_CONTACT:
			for (j = i + 1; j < *pCurCnt; j++) {
				contacts[j - 1] = contacts[j];
			}
			memset(&contacts[j], 0, sizeof(CONTACT));
			(*pCurCnt)--;
			printf("연락처를 삭제했습니다.\n");
			break;
		}
	}
}