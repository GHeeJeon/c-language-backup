#include<stdio.h>

int num = 0; int evenNum = 0; int oddNum = 0;
int cnt = 0; int evenCnt = 0; int oddCnt = 0;

void assignmnetMethod() {
	for (;;) {
		printf("정수 입력 : ");
		scanf_s("%d", &num);

		if (num == -1)      //입력받은 정수가 -1일 경우 종료
			break;

		if (num % 2 == 0)   //짝수일 경우
		{
			evenNum += num;   //짝수의 총합
			evenCnt++;   //짝수가 입력된 횟수
		}
		else
		{
			oddNum += num;   //홀수의 총합
			oddCnt++;      //홀수가 입력된 횟수
		}
		cnt++;      //전체 입력횟수(데이터 갯수) 증가
	}
}

void printData(){
	printf("++++++++++\n");
	printf("데이터 개수 : %d\n", cnt);
	printf(" 아하기시러");
	printf("");
	printf("");
	printf("");
}
int main(void) {
	assignmnetMethod();
	printData();
	return 0;
}