/* Menu.c */
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include "Menu.h"

int SelectMenu(void)
{
    int choice;

    while(1)
    {
        int result;

        printf("\n-------------------\n");
        printf("1. 연락처 추가\n");
        printf("2. 전체 연락처 목록\n");
        printf("3. 연락처 검색\n");
        printf("0. 종료\n");
        printf("-------------------\n");
        printf("메뉴 선택 : ");

        result = scanf("%d", &choice);
        CLEAR_INPUT();
        if( result == 0 )
        {
            printf("잘못 입력하셨습니다.\n");
            continue;
        }

        if( choice >= 0 && choice <= 3 )
            return choice;
        else
        {
            printf("잘못 입력하셨습니다.\n");
            continue;
        }
    }
}

int SelectFindMenu(void)
{
    int choice;
    int result;

    while( 1 )
    {
        printf("\n-------------------\n");
        printf("1. 연락처 수정\n");
        printf("2. 연락처 삭제\n");
        printf("0. 이전 메뉴\n");
        printf("-------------------\n");
        printf("메뉴 선택 : ");

        result = scanf("%d", &choice);
        CLEAR_INPUT();
        if( result == 0 )
        {
            printf("잘못 입력하셨습니다.\n");
            continue;
        }

        if( choice >= 0 && choice <= 2 )
            return choice;
        else
        {
            printf("잘못 입력하셨습니다.\n");
            continue;
        }
    }
}
