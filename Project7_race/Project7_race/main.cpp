#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include "horserace.h"
using namespace std;

Horse::Horse() {
	this->name = 0;
	this->move = 0;
}

HorseManager::HorseManager(int horseNum) {

}

HorseManager::~HorseManager() {      //소멸자
	delete[] p;
}

void Horse::nameSet(int name) {
	this->name = name;
}
void Horse::setMove(int move) {
	this->move = move;
}
void Horse::moving(int move) {
	this->move = move;
}

void HorseManager::getHorseNum(int horseNum) {
	const int const_horseNum = horseNum;
	return;
}

void HorseManager::gotoxy(int x, int y) {   //콘솔 사용을 위한 함수
	COORD posXY = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), posXY);
}

void HorseManager::horseSetting() {
	cout << "경마 게임!" << endl;
	cout << "몇 마리의 말로 플레이하시겠습니까?" << endl;

	while (true) {

		cin >> horseNum;
		HorseManager::getHorseNum(horseNum);
		if (!cin) {
			cout << "잘못된 숫자입력입니다.\n다시 입력해주세요" << endl;
			cin.clear();      //상태플러그 초기화
			cin.ignore(INT_MAX, '\n');      //버퍼값 한꺼번에 지우기
		}
		else {

			if (2 <= horseNum && horseNum <= 5) {   //2~5마리
				break;
			}
			else if (2 > horseNum) {      //2마리 미만
				cout << "최소 2마리의 말이 필요합니다.\n다시 입력해주세요" << endl;
			}

			else if (horseNum > 5) {      //5마리 초과
				cout << "최대 5마리의 말까지 플레이 가능합니다.\n다시 입력해주세요" << endl;
			}

			else {
				cout << "잘못된 숫자입력입니다.\n다시 입력해주세요" << endl;
			}

		}
	}

	cout << "몇 번째 말을 선택하시겠습니까?" << endl;
	while (true) {

		cin >> choose;      //말 선택

		if (!cin) {
			cout << "잘못된 숫자입력입니다.\n다시 입력해주세요" << endl;
			cin.clear();      //상태플러그 초기화
			cin.ignore(INT_MAX, '\n');      //버퍼값 한꺼번에 지우기
		}
		else {

			if (1 <= choose && choose <= horseNum) {   //넘버 horseNum으로 변경
				break;
			}
			else if (1 > choose || choose > horseNum) {
				cout << "잘못된 입력입니다. 입력은 1 이상 " << horseNum << " 이하여야 합니다." << endl;
			}

			else {
				cout << "잘못된 입력입니다.\n다시 입력해주세요" << endl;
			}
		}
	}
	//cout << "세팅완료";	//디버깅용
}

void HorseManager::horseAreRunning() {

	p = new Horse[horseNum];
	for (int i = 0; i < horseNum; i++) {   //말 이름(번호) 설정
		(p + i)->nameSet(i + 1);
		//cout << p[i].getName();   //디버깅용, 이름이 잘 들어갔는지 확인
	}

	system("cls");
	cout << endl;
	cout << "고른 말 번호: " << choose << endl;
	cout << "진행 턴수: ";
	cout << "\n-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_";

	for (int i = 0; i < horseNum; i++)      //시작점에 말 번호 출력
	{
		gotoxy(0, 5 + i * 2);
		cout << i + 1;
	}

	cout << endl << endl << "경주 시작!" << endl;

	while (ranking != horseNum)	//모든 말의 등수가 정해졌을 경우
	{
		
		for (int i = 0; i < horseNum; i++) {
			Sleep(500);		//말 이동 딜레이
			if (rank[i] != 0)
				continue;

				for (int i = 0; i < horseNum; i++) {
					movemove = rand() % 6;		//0~5
					int m2 = p[i].getMove() + movemove;//더한 값
					p[i].setMove(m2);
					if (m2 > 19) {	// 골인: 20
						m2 = 20;	//20 이상이면 무조건 20으로
						p[i].setMove(m2);
						if (!rank[i]) {
							ranking++;	//0등이 아닌, 1등부터 받기
							rank[i] = p[i].getName();	//20도달하면 저장			
							gotoxy(35, 3 + p[i].getName() * 2);
							cout << "  " << ranking << "등";
							if (ranking == 1){		//1등일 경우
								 win = p[i].getName();	//1등변수에 말이름 저장
							}
						}
					}	
					gotoxy(3, 3 + p[i].getName() * 2);
					for (int k = 0; k < p[i].getMove(); k++)
						cout << " ";		//이동 수만큼 출력
					if (p[i].getMove())
						cout << ")) ~nn^ " << p[i].getMove();	//말친구 출력
				}
			gotoxy(11, 2);
			cout << turn++;      //턴 수
		}
	}
	gotoxy(0, 15);
	cout << "게임 종료!" << endl;
	
	cout << win << "번째 말이 우승했습니다!" << endl;	//1등변수

	if (choose == win)	//1등변수(말 이름)와 선택한 말이 같을 경우
		cout << "우승 말을 맞췄습니다!" << endl;
	else
		cout << "우승 말을 맞추지 못했습니다..." << endl;
}

int main() {
	srand((unsigned int)time(nullptr));
	HorseManager myHorseManager;
	myHorseManager.horseSetting();
	myHorseManager.horseAreRunning();

	return 0;
}