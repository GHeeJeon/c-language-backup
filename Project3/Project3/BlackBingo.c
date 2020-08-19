#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void GameStart();
void Win_or_Lose();
void Search_user();
void Search_com();

int u_checkOverlap[50] = { 0 };
int c_checkOverlap[50] = { 0 };
int userBingo[5][5] = { 0 };//2
int comBingo[5][5] = { 0 };//2
int Proto_userBingo[5][5] = { 0 };
int Proto_comBingo[5][5] = { 0 };
int userSum = 0;//
int comSum = 0;
int turnCount = 0;//
int eraseNumber;//
int eraseNumber_C;//
int uNum;//
int cNum;//
int erasenumber;//
int i, j, k, l;//
int search_u_i, search_u_j, search_c_k, search_c_l;//

int main()//
{
	char menukey;

	while (1)//do_whilefor(;;)
	{
		printf("s\n");
		printf("q\n");
		printf("x\n");
		printf("");
		scanf("%c", &menukey);

		getchar();//'\n'

		system("cls");//

		if (menukey == 's')
		{
			GameStart();//
		}
		else if (menukey == 'q')//
		{
			printf("s\n");
			printf("\n");
			printf("150 25\n");
			printf("\n");
			printf("\n");
			printf("\n");
			printf("\n");
			printf("\n");

		}
		else if (menukey == 'x')
		{
			return 0;//
		}
		else
		{
			printf("\n");
		}
	}
}
void Win_or_Lose()
{
	if (userSum == 25 && comSum == 25)
	{
		printf("\n");//
		printf(Proto_userBingo[i][j], Proto_comBingo[k][l], "\n");//
		printf(userBingo[i][j], comBingo[k][l], "\n");
		main();
	}
	else if (uNum == 25)
	{
		printf("\n");
		printf(Proto_userBingo[i][j], Proto_comBingo[k][l], "\n");
		printf(userBingo[i][j], comBingo[k][l], "\n");
		main();
	}
	else if (cNum == 25)
	{
		printf("\n");
		printf(Proto_userBingo[i][j], Proto_comBingo[k][l], "\n");
		printf(userBingo[i][j], comBingo[k][l], "\n");
		main();
	}
	else
	{
		printf("\n");//
		turnCount = turnCount + 1;
	}
}

void Search_user()
{
	printf("");
	scanf("%d", &eraseNumber);

	while (eraseNumber < 1 || eraseNumber > 50)//
	{
		printf("150\n");
		printf("");
		scanf("%d", &eraseNumber);
	}

	for (search_u_i = 0; search_u_i < 5; search_u_i++)//
	{
		for (search_u_j = 0; search_u_j < 5; search_u_j++)
		{
			while (userBingo[search_u_i][search_u_j] != eraseNumber)//
			{
				printf("\n");
				printf("");
				scanf("%d", &eraseNumber);//
			}
		}
		for (search_c_k = 0; search_c_k < 5; search_c_k++)//
		{
			for (search_c_l = 0; search_c_l < 5; search_c_l++)
			{
				if (userBingo[search_u_i][search_u_j] == eraseNumber && comBingo[search_c_k][search_c_l] == eraseNumber)
				{
					printf("%d\n", eraseNumber);
					eraseNumber = 0;
					userBingo[i][j] = userBingo[search_u_i][search_u_j];
					comBingo[i][j] = comBingo[search_u_i][search_u_j];
					printf(userBingo[search_u_i][search_u_j]);
					printf(comBingo[search_c_k][search_c_l]);
					userSum = userSum + 1;
					comSum = comSum + 1;
					Win_or_Lose();//
					Search_com();
				}
				else
				{
					printf("%d\n", eraseNumber);
					eraseNumber = 0;
					userSum = userSum + 1;
					Win_or_Lose();
					Search_user();//
				}
			}
		}
	}
}

void Search_com()
{
	srand((unsigned)time(NULL));//
	eraseNumber = rand() % 50 + 1;
	for (search_c_k = 0; search_c_k < 5; search_c_k++)
	{
		for (search_c_l = 0; search_c_l < 5; search_c_l++)
		{
			while (comBingo[i][j] != eraseNumber)
			{
				eraseNumber = rand() % 50 + 1;
			}
			for (search_u_i = 0; search_u_i < 5; search_u_i++)//
			{
				if (comBingo[search_c_k][search_c_l] == eraseNumber && userBingo[search_u_i][search_u_j] == eraseNumber)
				{
					printf("%d\n", eraseNumber);
					eraseNumber = 0;
					Win_or_Lose();//
				}
				else
				{
					Win_or_Lose();
					Search_com();//
				}

			}

		}
	}
}


void GameStart()//
{
	srand((unsigned)time(NULL));//

	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5; j++)
		{
			eraseNumber = rand() % 50;
			if (u_checkOverlap[eraseNumber] == 1)//
			{
				j--;//
				continue;//
			}
			u_checkOverlap[eraseNumber] = 1;//
			userBingo[i][j] = eraseNumber + 1;//
		}
	}
	for (i = 0; i < 5; i++)//
	{
		for (j = 0; j < 5; j++)
			printf("%4d", userBingo[i][j]);
		printf("\n");
	}

	for (k = 0; k < 5; k++)//
	{
		for (l = 0; l < 5; l++)
		{
			eraseNumber = rand() % 50;
			if (c_checkOverlap[eraseNumber] == 1)//
			{
				l--;//
				continue;
			}
			c_checkOverlap[eraseNumber] = 1;//
			comBingo[k][l] = eraseNumber + 1;//
		}
	}
	/*for (k = 0; k < 5; k++)//
	{
	for (l = 0; l < 5; l++)
	printf("%4d", comBingo[k][l]);
	printf("\n");
	}*/

	if (turnCount == 0)
	{
		Proto_userBingo[5][5] = userBingo[i][j];//
		Proto_comBingo[5][5] = comBingo[k][l];
		printf("\n");
	}
	else
	{

	}

	for (;;)
	{
		Search_user();
		Search_com();
	}
}
