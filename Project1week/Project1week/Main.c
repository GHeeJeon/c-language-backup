/* Main.c */
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include "Contact.h"
#include "Menu.h"

int main(void)
{
	CONTACT *contacts = NULL;
	int max_contacts = 0;
	int contacts_cnt = 0;
	int menu = 0;
	do {
		printf("�ִ� ����ó�� ������ �Է��ϼ��� : ");
		if (scanf("%d", &max_contacts) == 0)
		{
			printf("�߸� �Է��ϼ̽��ϴ�.\n");
			CLEAR_INPUT();
			continue;
		}
	} while (max_contacts <= 0);

	contacts = Initialize(max_contacts);
	if (contacts == NULL)
	{
		printf("���� �޸� �Ҵ� ����\n");
		exit(1);
	}

	while (1)
	{
		menu = SelectMenu();
		if (menu == QUIT_PROGRAM)
			break;
		switch (menu)
		{
		case ADD_CONTACT:
			if (AddContactInfo(contacts, max_contacts, &contacts_cnt) != 0)
			{
				printf("����ó�� �߰��Ǿ����ϴ�.\n");
			}
			break;
		case LIST_BY_NAME:
			ListByName(contacts, contacts_cnt);
			break;
		}
	}
}