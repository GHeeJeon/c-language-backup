#pragma once
#define __HORSE_H
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;

class Horse {
	int name;
	int move;      //말 이동 변수
public:
	Horse();
	int getName() { return name; }
	int getMove() { return move; }
	void setMove(int move);
	void nameSet(int name);
	void moving(int move);
};


class HorseManager {
	Horse* p;
	int horseNum;      //말 마리 수
	int choose;      //고른 말 넘버
	int ranking;      //등수
	int turn;         //턴
	int rank[5];      //도착한 말 저장
	int movemove;		//말 이동 칸 수
	int win;			//1등 말
public:
	HorseManager() : horseNum{ 0 }, choose{ 0 }, ranking{ 0 }, turn{ 1 }, movemove{ 0 }, rank{ 0, }, win{ 0 } {}
	HorseManager(int horseNum);
	int getHorseNum() { return horseNum; }   //프라이빗 변수 받기
	void gotoxy(int x, int y);      //좌표값
	void getHorseNum(int horseNum);   //horseNum 상수로 받기
	void horseSetting();   //게임 셋팅
	void horseAreRunning();//본격 게임기능
	~HorseManager();
};


