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
    if( p != NULL )
        memset(p, 0, sizeof(CONTACT) * totalCnt);
    return p;
}

int AddContactInfo(CONTACT *contacts, int maxCnt, int *pCurCnt)
{
    CONTACT *p = NULL;
    int ring;
	int Err = 1;
	int i = 0;
    if( maxCnt == *pCurCnt )
        return 0;

    p = &contacts[*pCurCnt];
	while (Err != 0)
	{
		printf("\n��    �� : ");
		fgets(p->name, MAX_STR, stdin);
		for (i = 0;i < MAX_STR-1;i++)
		{
			if (p->name[1] == NULL)
			{
				printf("\n�̸��� �Է��ϼ���.\n");
				Err = 1;
				break;
			}
			else
				Err = 0;
		}
	}
	Err = 1;
	p->name[strlen(p->name) - 1] = '\0';  // �ٹٲ� ���� ����
	while (Err != 0)
	{
		printf("��ȭ��ȣ : ");
		fgets(p->phone, MAX_STR, stdin);
			if (p->phone[1] == NULL)
			{
				printf("\n��ȣ�� �Է��ϼ���\n");
				Err = 1;
			}
			else
				Err = 0;
	}
	p->phone[strlen(p->phone) - 1] = '\0'; // �ٹٲ� ���� ����

    do {
        printf("[1.��ȭ�� 2.�ǾƳ� 3.������ 4.����] ���Ҹ� ���� : ");
        scanf("%d", &ring);
        CLEAR_INPUT( );
    } while( ring < 0 || ring > 4 );
    p->ring = ring - 1;

    ( *pCurCnt )++;
    return *pCurCnt;
}

void ListByName(CONTACT *contacts, int cnt)
{
    if( cnt == 0 )
    {
        printf("����� ������ �����ϴ�.\n");
        return;
    }
    qsort(contacts, cnt, sizeof(CONTACT), CompareByName);
    PrintAllContacts(contacts, cnt);
}

void PrintAllContacts(const CONTACT *contacts, int cnt)
{
    int i;
    const char* ringtones[] = {
        "��ȭ��", "�ǾƳ�", "������", "����"
    };

    printf("\n==================================\n");
    printf(" �̸�        ��ȭ��ȣ     ���Ҹ�\n");
    printf("==================================\n");
    for( i = 0; i < cnt; i++ )
    {
        printf("%-10s %-14s %s\n", contacts[i].name, contacts[i].phone,
            ringtones[contacts[i].ring]);
    }
    printf("==================================\n");
}

int CompareByName(const void* e1, const void* e2)
{
    const CONTACT *p1 = (const CONTACT*) e1;
    const CONTACT *p2 = (const CONTACT*) e2;
    return strcmp(p1->name, p2->name);
}

CONTACT* ExpandContacts(CONTACT *contacts, int *pMaxCnt)
{
    CONTACT *temp = realloc(contacts, sizeof(CONTACT)*(*pMaxCnt)*2);
    if( temp == NULL )
        return NULL;
    *pMaxCnt = *pMaxCnt * 2;
    return temp;
}

void FindContact(CONTACT *contacts, int *pCurCnt)
{
    char name[MAX_STR];
    CONTACT *p = NULL;
    int i, j;
    int findMenu = 0;
    int ring;
	int Err=0;
    printf("ã�� �̸� : ");
    fgets(name, MAX_STR, stdin);
    name[strlen(name) - 1] = '\0';  // �ٹٲ� ���� ����

    for( i = 0; i < *pCurCnt; i++ )
    {
        if( _strcmpi(contacts[i].name, name) == 0 )
        {
            p = &contacts[i];
            break;
        }
    }

    if( p == NULL )
    {
        printf("����ó�� ã�� �� �����ϴ�.\n");
        return;
    }

    printf("%-10s %-14s\n", contacts[i].name, contacts[i].phone);

    while( 1 )
    {
        findMenu = SelectFindMenu( );
        if( findMenu == PREVIOUS_MENU )
            break;
        switch( findMenu )
        {
        case MODIFY_CONTACT:
			while (Err != 0)
			{
				printf("\n��    �� : ");
				fgets(p->name, MAX_STR, stdin);
				for (i = 0;i < MAX_STR - 1;i++)
				{
					if (p->name[1] == NULL)
					{
						printf("\n�̸��� �Է��ϼ���.\n");
						Err = 1;
						break;
					}
					else
						Err = 0;
				}
			}
			Err = 1;
			p->name[strlen(p->name) - 1] = '\0';  // �ٹٲ� ���� ����
			while (Err != 0)
			{
				printf("��ȭ��ȣ : ");
				fgets(p->phone, MAX_STR, stdin);
				if (p->phone[1] == NULL)
				{
					printf("\n��ȣ�� �Է��ϼ���\n");
					Err = 1;
				}
				else
					Err = 0;
			}
			p->phone[strlen(p->phone) - 1] = '\0'; // �ٹٲ� ���� ����

            do {
                printf("[1.��ȭ�� 2.�ǾƳ� 3.������ 4.����] ���Ҹ� ���� : ");
                scanf("%d", &ring);
                CLEAR_INPUT( );
            } while( ring < 0 || ring > 4 );
            p->ring = ring - 1;
            printf("����ó�� �����߽��ϴ�.\n");
            break;
        case DELETE_CONTACT:
            for( j = i + 1; j < *pCurCnt; j++ )
            {
                contacts[j - 1] = contacts[j];
            }
            memset(&contacts[j], 0, sizeof(CONTACT));
            ( *pCurCnt )--;
            printf("����ó�� �����߽��ϴ�.\n");
            break;
        }
    }
}