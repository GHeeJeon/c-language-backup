#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
void gotoxy(int x, int y);

int main(void)
{
	int horse_num, i, number, k, max = 0, count = 0, rank[10] = { 0 };
	int horse[5] = { 0 }, race;
	char horse_name[10][10];
	int turn = 0;
	srand(time(NULL));
	printf("�渶����\n\n");
	printf("������ ���� ����(�ִ� 5)�� �Է��ϰ� Enter>");
	scanf_s("%d", &horse_num);
	printf("\n\n");
	//printf("%d�� ���� �̸�(�ִ� �ѱ� 3��)�� �Է��ϰ� enter�ϼ���.\n", horse_num);
	//printf("\n");
	//for (i = 0; i < horse_num; i++)
	//{
	//	printf("%d�� �� �̸� :", i + 1);
	//	fflush(stdin);
	//	scanf_s("%s", horse_name[i]);
	//}
	system("cls");
	printf("\n\n");
	printf("���� �ϼ�:");
	printf("\n-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n");

	for (i = 0; i < horse_num; i++)
	{
		gotoxy(1, 5 + i * 2);
		printf("%d", i+1);
	}
	printf("\n\n���� ����!\n");
	_getch();
	while (count != horse_num)
	{
		number = rand() % horse_num;		//number = ������ �̵���ų����?
		if (rank[number] != 0)
			continue;
		race = rand() % 5 + 1;		//race�� �̵��� ĭ��!
		horse[number] = horse[number] + race;	//���� ��
		Sleep(300);
		if (horse[number] > 19)	//�ʰ��ϸ� �׳� 20���� ����������~
		{
			horse[number] = 20;
			if (!rank[number])		//��� �ű��
			{
				count++;		//���
				rank[number] = count; 
				gotoxy(3, 5 + number * 2);
				for (k = 0; k < horse[number]; k++)
					printf("-");
				if (horse[number])
					printf("~nn^ %d", horse[number]);
				gotoxy(35, 5 + number * 2);
				printf("   %d��    ", count);
			}
		}
		else		//20�� ���� �ȵ��� ���
		{
			gotoxy(3, 5 + number * 2);
			for (k = 0; k < horse[number]; k++)
				printf("-");
			if (horse[number])
				printf("~nn^ %d", horse[number]);
		}
		gotoxy(11, 3);
		printf(" %d", turn++);
	}
	gotoxy(1, 20);
	printf("���� ����!\n");
	return 0;
}

void gotoxy(int x, int y)
{
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}