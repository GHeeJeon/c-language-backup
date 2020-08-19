/* Main.c */
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include "Contact.h"
#include "Menu.h"
#include "FileIo.h"

int main(void)
{
    CONTACT *contacts = NULL;
    int max_contacts = 0;
    int contacts_cnt = 0;
    int menu = 0;
	int searchChoice = -1;
    FILE *fp = NULL;

    fp = fopen("test.dat", "rb");
    if( fp != NULL )
    {
        ReadData(fp, &contacts, &max_contacts, &contacts_cnt);
        printf("������ ������ �о�ɴϴ�.\n");
        printf("�ִ� ����ó ���� : %d, ���� ����ó ���� : %d\n",
            max_contacts, contacts_cnt);
        fclose(fp);
    }
    else
    {
        do {
            printf("�ִ� ����ó�� ������ �Է��ϼ��� : ");
            if( scanf("%d", &max_contacts) == 0 )
            {
                printf("�߸� �Է��ϼ̽��ϴ�.\n");
                CLEAR_INPUT();
                continue;
            }
        } while( max_contacts <= 0 );

        contacts = Initialize(max_contacts);
        if( contacts == NULL )
        {
            printf("���� �޸� �Ҵ� ����\n");
            exit(1);
        }
    }

    while( 1 )
    {
        menu = SelectMenu();
        if( menu == QUIT_PROGRAM )
            break;
        switch( menu )
        {
        case ADD_CONTACT:
            if( AddContactInfo(contacts, max_contacts, &contacts_cnt) == 0 )
            {
                CONTACT *temp = ExpandContacts(contacts, &max_contacts);
                if( temp == NULL )
                {
                    printf("�� �̻� ����ó�� �߰��� �� �����ϴ�.\n");
                }
                else
                {
                    contacts = temp;
                    printf("�ִ� ���� ������ ����ó�� ������ %d�� �ø��ϴ�.\n", max_contacts);
                }
            }
            break;
        case LIST_BY_NAME:
            ListByName(contacts, contacts_cnt);
            break;
        case FIND_CONTACT:
			while (1) {
				printf("����ó�� ��ȭ��ȣ�� ��ɷ� �˻��Ͻðڽ��ϱ�?\n");
				printf("����ó �˻��� 1, ��ȭ��ȣ �˻��� 2 �� �����ּ���.");
				scanf("%d", &searchChoice);
				CLEAR_INPUT();
				if (searchChoice == 1) {
					FindContact(contacts, &contacts_cnt);
					searchChoice = 0;
					break;
				}
				else if (searchChoice == 2) {
					PhoneContact(contacts, &contacts_cnt);
					searchChoice = 0;
					break;
				}
				else
					printf("1�� 2�� �Է����ּ���.");
			}
			break;
        }
    }

    fp = fopen("test.dat", "wb");
    if( fp != NULL )
    {
        WriteData(fp, contacts, max_contacts, contacts_cnt);
        printf("\n������ ������ �����մϴ�.\n");
        printf("�ִ� ����ó ���� : %d, ���� ����ó ���� : %d\n",
            max_contacts, contacts_cnt);
        fclose(fp);
    }

    free(contacts);
    contacts = NULL;

    return 0;
}