#include<stdio.h>

int num = 0; int evenNum = 0; int oddNum = 0;
int cnt = 0; int evenCnt = 0; int oddCnt = 0;

void assignmnetMethod() {
	for (;;) {
		printf("���� �Է� : ");
		scanf_s("%d", &num);

		if (num == -1)      //�Է¹��� ������ -1�� ��� ����
			break;

		if (num % 2 == 0)   //¦���� ���
		{
			evenNum += num;   //¦���� ����
			evenCnt++;   //¦���� �Էµ� Ƚ��
		}
		else
		{
			oddNum += num;   //Ȧ���� ����
			oddCnt++;      //Ȧ���� �Էµ� Ƚ��
		}
		cnt++;      //��ü �Է�Ƚ��(������ ����) ����
	}
}

void printData(){
	printf("++++++++++\n");
	printf("������ ���� : %d\n", cnt);
	printf(" ���ϱ�÷�");
	printf("");
	printf("");
	printf("");
}
int main(void) {
	assignmnetMethod();
	printData();
	return 0;
}