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
        printf("1. ����ó �߰�\n");
        printf("2. ��ü ����ó ���\n");
        printf("3. ����ó �˻�\n");
        printf("0. ����\n");
        printf("-------------------\n");
        printf("�޴� ���� : ");

        result = scanf("%d", &choice);
        CLEAR_INPUT();
        if( result == 0 )
        {
            printf("�߸� �Է��ϼ̽��ϴ�.\n");
            continue;
        }

        if( choice >= 0 && choice <= 3 )
            return choice;
        else
        {
            printf("�߸� �Է��ϼ̽��ϴ�.\n");
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
        printf("1. ����ó ����\n");
        printf("2. ����ó ����\n");
        printf("0. ���� �޴�\n");
        printf("-------------------\n");
        printf("�޴� ���� : ");

        result = scanf("%d", &choice);
        CLEAR_INPUT();
        if( result == 0 )
        {
            printf("�߸� �Է��ϼ̽��ϴ�.\n");
            continue;
        }

        if( choice >= 0 && choice <= 2 )
            return choice;
        else
        {
            printf("�߸� �Է��ϼ̽��ϴ�.\n");
            continue;
        }
    }
}
