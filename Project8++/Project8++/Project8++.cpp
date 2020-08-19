#include<iostream>
#include<string>
#include<fstream>
#include<vector>
using namespace std;

class Temp
{
public:
	string time;
	string temperature;
	string getTime() { return time; }
	string getTemperature() { return temperature; }
	//friend istream& operator >> (istream& ins, const Temp& t);
	friend ostream& operator << (ostream& outs, const Temp t);
};

//istream& operator >> (istream& ins, const Temp& t)	//입력
//{
//
//}

ostream& operator << (ostream& outs, const Temp t)	//출력
{
	int i;
	outs.width(2);
	outs << t.time << "시: 온도 ";
	for (i = 0; i < 5; i++)
	{
		outs << t.temperature[i];
	}
	outs << '\n';
	return outs;
}

class TempManager {
	vector<Temp> tem;
	string n;
	string m;
public:

	void phase1();// 한 파일을 열고 내용을 불러온 다음
	void phase2();//불러온 내용을 다시 같은 파일에 쓰고 다시 출력
	void phase3();//내용을 다시 불러와서
	void phase4();//'다른파일'에 쓰고 '다른파일' 불러와서 출력 
};

void TempManager::phase1()	
{
	ifstream fin;
	Temp temp_temp;

	fin.open("temp.txt");
	if (!fin){
		cout << "파일을 열 수 없습니다.";
		return;
	}
	while (getline(fin, n, ' ')){	//파일 -> c로
		getline(fin, m);
		temp_temp.time = n;
		temp_temp.temperature = m;
		tem.push_back(temp_temp);
	}
	for (int i = 0; i < tem.size(); i++){	//출력
		cout << tem[i];
	}
	fin.close();	//닫기
	cout << "1페이즈 종료\n\n";
}
void TempManager::phase2()
{	
	vector<Temp>::iterator it;
	ofstream fout("temp.txt");
	if (!fout) // 파일 생성 실패
		cout << "\n파일 쓰기에 실패하였습니다.\n";
	else {
		for (it = tem.begin(); it != tem.end(); it++)
			fout << (*it).getTime() << ' ' << (*it).getTemperature() << "\n";
		cout << "c -> 파일 덮어쓰기 완료\n";
	}

	ifstream fin;//불러와서 출력
	Temp temp_temp;

	fin.open("temp.txt");
	if (!fin) {
		cout << "파일을 열 수 없습니다.";
		return;
	}
	while (getline(fin, n, ' ')) {	//파일 -> c로 저장
		getline(fin, m);
		temp_temp.time = n;
		temp_temp.temperature = m;
		tem.push_back(temp_temp);
	}
	for (int i = 0; i < tem.size(); i++) {	//출력
		cout << tem[i];
	}
	cout << "출력완료\n";
	fout.close();
	cout << "2페이즈 종료\n\n";
}
void TempManager::phase3() {
	ifstream fin;
	Temp temp_temp;

	fin.open("temp.txt");
	if (!fin) {
		cout << "파일을 열 수 없습니다.";
		return;
	}
	while (getline(fin, n, ' ')) {	//파일 -> c로 저장
		getline(fin, m);
		temp_temp.time = n;
		temp_temp.temperature = m;
		tem.push_back(temp_temp);
	}
	cout << "파일 -> c 불러오기 완료\n";
	cout << "3페이즈 종료\n\n";
}

void TempManager::phase4() {
	vector<Temp>::iterator it;
	ofstream fout("temp1.txt");
	if (!fout) // 파일 생성 실패
		cout << "\n파일 쓰기에 실패하였습니다.\n";
	else {
		for (it = tem.begin(); it != tem.end(); it++)
			fout << (*it).getTime() << ' ' << (*it).getTemperature() << "\n";
		cout << "c -> 새파일 덮어쓰기 완료\n";
	}
	fout.close();

	ifstream fin;//불러와서 출력
	Temp temp_temp;

	fin.open("temp1.txt");
	if (!fin) {
		cout << "파일을 열 수 없습니다.";
		return;
	}
	while (getline(fin, n, ' ')) {	//파일 -> c로 저장
		getline(fin, m);
		temp_temp.time = n;
		temp_temp.temperature = m;
		tem.push_back(temp_temp);
	}
	for (int i = 0; i < tem.size(); i++) {	//출력
		cout << tem[i];
	}
	cout << "새 파일 -> c 출력완료\n";
	fin.close();
	cout << "4페이즈 종료\n\n";
}

int main()
{
	TempManager manager;
	manager.phase1();
	manager.phase2();
	manager.phase3();
	manager.phase4();
}