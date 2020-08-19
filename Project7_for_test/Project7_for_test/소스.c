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
	printf("경마게임\n\n");
	printf("경주할 말의 숫자(최대 5)를 입력하고 Enter>");
	scanf_s("%d", &horse_num);
	printf("\n\n");
	//printf("%d개 말의 이름(최대 한글 3자)을 입력하고 enter하세요.\n", horse_num);
	//printf("\n");
	//for (i = 0; i < horse_num; i++)
	//{
	//	printf("%d번 말 이름 :", i + 1);
	//	fflush(stdin);
	//	scanf_s("%s", horse_name[i]);
	//}
	system("cls");
	printf("\n\n");
	printf("진행 턴수:");
	printf("\n-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n");

	for (i = 0; i < horse_num; i++)
	{
		gotoxy(1, 5 + i * 2);
		printf("%d", i+1);
	}
	printf("\n\n경주 시작!\n");
	_getch();
	while (count != horse_num)
	{
		number = rand() % horse_num;		//number = 누구를 이동시킬건지?
		if (rank[number] != 0)
			continue;
		race = rand() % 5 + 1;		//race는 이동할 칸수!
		horse[number] = horse[number] + race;	//더한 값
		Sleep(300);
		if (horse[number] > 19)	//초과하면 그냥 20으로 만들어버리기~
		{
			horse[number] = 20;
			if (!rank[number])		//등수 매기기
			{
				count++;		//등수
				rank[number] = count; 
				gotoxy(3, 5 + number * 2);
				for (k = 0; k < horse[number]; k++)
					printf("-");
				if (horse[number])
					printf("~nn^ %d", horse[number]);
				gotoxy(35, 5 + number * 2);
				printf("   %d등    ", count);
			}
		}
		else		//20이 아직 안됐을 경우
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
	printf("게임 종료!\n");
	return 0;
}

void gotoxy(int x, int y)
{
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}