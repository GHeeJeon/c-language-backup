#pragma once
#define __HORSE_H
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;

class Horse {
	int name;
	int move;      //�� �̵� ����
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
	int horseNum;      //�� ���� ��
	int choose;      //�� �� �ѹ�
	int ranking;      //���
	int turn;         //��
	int rank[5];      //������ �� ����
	int movemove;		//�� �̵� ĭ ��
	int win;			//1�� ��
public:
	HorseManager() : horseNum{ 0 }, choose{ 0 }, ranking{ 0 }, turn{ 1 }, movemove{ 0 }, rank{ 0, }, win{ 0 } {}
	HorseManager(int horseNum);
	int getHorseNum() { return horseNum; }   //�����̺� ���� �ޱ�
	void gotoxy(int x, int y);      //��ǥ��
	void getHorseNum(int horseNum);   //horseNum ����� �ޱ�
	void horseSetting();   //���� ����
	void horseAreRunning();//���� ���ӱ��
	~HorseManager();
};


