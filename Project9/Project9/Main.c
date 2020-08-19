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
        printf("데이터 파일을 읽어옵니다.\n");
        printf("최대 연락처 개수 : %d, 현재 연락처 개수 : %d\n",
            max_contacts, contacts_cnt);
        fclose(fp);
    }
    else
    {
        do {
            printf("최대 연락처의 개수를 입력하세요 : ");
            if( scanf("%d", &max_contacts) == 0 )
            {
                printf("잘못 입력하셨습니다.\n");
                CLEAR_INPUT();
                continue;
            }
        } while( max_contacts <= 0 );

        contacts = Initialize(max_contacts);
        if( contacts == NULL )
        {
            printf("동적 메모리 할당 실패\n");
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
                    printf("더 이상 연락처를 추가할 수 없습니다.\n");
                }
                else
                {
                    contacts = temp;
                    printf("최대 저장 가능한 연락처의 개수를 %d로 늘립니다.\n", max_contacts);
                }
            }
            break;
        case LIST_BY_NAME:
            ListByName(contacts, contacts_cnt);
            break;
        case FIND_CONTACT:
			while (1) {
				printf("연락처와 전화번호중 어떤걸로 검색하시겠습니까?\n");
				printf("연락처 검색은 1, 전화번호 검색은 2 를 눌러주세요.");
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
					printf("1과 2를 입력해주세요.");
			}
			break;
        }
    }

    fp = fopen("test.dat", "wb");
    if( fp != NULL )
    {
        WriteData(fp, contacts, max_contacts, contacts_cnt);
        printf("\n데이터 파일을 저장합니다.\n");
        printf("최대 연락처 개수 : %d, 현재 연락처 개수 : %d\n",
            max_contacts, contacts_cnt);
        fclose(fp);
    }

    free(contacts);
    contacts = NULL;

    return 0;
}