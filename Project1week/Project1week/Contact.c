/* Contact.c */
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "menu.h"

CONTACT* Initialize(int totalCnt)
{
	CONTACT *p = malloc(sizeof(CONTACT) * totalCnt);
	if (p != NULL)
		memset(p, 0, sizeof(CONTACT) * totalCnt);
	return p;
}

int AddContactInfo(CONTACT *contacts, int maxCnt, int *pCurCnt)
{
	CONTACT *p = NULL;
	int ring;

	if (maxCnt == *pCurCnt)
		return 0;

	p = &contacts[*pCurCnt];
	printf("\n이    름 : ");
	fgets(p->name, MAX_STR, stdin);
	p->name[strlen(p->name) - 1] = '\0';  // 줄바꿈 문자 제거
	printf("전화번호 : ");
	fgets(p->phone, MAX_STR, stdin);
	p->phone[strlen(p->phone) - 1] = '\0'; // 줄바꿈 문자 제거

	do {
		printf("[1.전화벨 2.피아노 3.마림바 4.하프] 벨소리 선택 : ");
		scanf("%d", &ring);
		CLEAR_INPUT();
	} while (ring < 0 || ring > 4);
	p->ring = ring - 1;

	(*pCurCnt)++;
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