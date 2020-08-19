#include <iostream>
#include <fstream>
#include <string> 
#include <ctime> 
#include <vector> 
#include <cstdlib> 
using namespace std;

class Nation {
	string nation;
	string capital;
public:
	Nation() { ; }
	Nation(string nation, string capital) {
		this->nation = nation;
		this->capital = capital;
	}
	string getCapital() { return capital; }
	string getNation() { return nation; }
	void set(string& n, string& c) { nation = n, capital = c; } 
	void setNation(string& n) { nation = n; } 
	void setCapital(string& c) { capital = c; } 
	friend istream& operator >> (istream& ins, Nation& n);	//삽입연산자 중복
	friend ostream& operator << (ostream& stream, Nation& n);	//추출연산자 중복
};

istream& operator>>(istream& ins, Nation& n) { //삽입 연산자
	cout << "나라를 입력하세요.(나라 입력값이 no면 입력끝)\n ";
	ins >> n.nation; 
	if (n.nation == "no")
		return ins;
		
	cout << "수도 이름을 입력하세요\n";
	ins >> n.capital; 
	return ins;
}

ostream& operator << (ostream& stream, Nation& n) { // 추출 연산자
	stream << n.getNation() << "-" << n.getCapital() << "\n";
	return stream;
}

class NationGame {
	vector<Nation> v;
	void input();
	void quiz();
	double quizNum{ 0 };
	double rightNum{ 0 };
	double correctRate{ 0 };
public:
	double getQuizNum() { return quizNum; }
	void setQuizNum(double quizNum) { this->quizNum = quizNum; }
	double getRightNum() { return rightNum; }
	void setRightNum(double rightNum) { this->rightNum = rightNum; }
	double getCorrectRate() { return correctRate; }
	void setCorrectRate(double correctRate) { this->correctRate = correctRate; }
	int gameStart();
	void sourceUpload();
	void change();
	void del();
	void backUp();
	void search();
	void show();
};

int NationGame::gameStart() {
	cout << "상식충전! 수도 맞추기 퀴즈\n\n";
	for (;;) {
		cout << "-------Menu-------\n";
		cout << "[1] 소스파일 업로드\n"; //txt에서 벡터로 받아오기
		cout << "[2] 정보 갱신\n";
		cout << "[3] 수도정보 검색\n";
		cout << "[4] 퀴즈\n";
		cout << "[5] 종료\n";
		cout << "선택: ";
		int select;
		cin >> select;
		if (!cin) {
			cout << "잘못된 숫자입력입니다.\n다시 입력해주세요\n\n";
			cin.clear();      //상태플러그 초기화
			cin.ignore(INT_MAX, '\n');      //버퍼값 한꺼번에 지우기
		}

		else if (select == 1) {
			sourceUpload();
		}
		else if (select == 2) {
			cout << "\n[정보 갱신]\n";
			cout << "(1) 수도이름 수정  (2) 새로운 나라 추가  (3) 나라 삭제  (4) 소스파일 백업\n";
			cout << "선택: ";
			select = 0;
			cin >> select;
			if (!cin) {
				cout << "잘못된 숫자입력입니다.\n다시 입력해주세요\n\n";
				cin.clear();      //상태플러그 초기화
				cin.ignore(INT_MAX, '\n');      //버퍼값 한꺼번에 지우기
			}
			else if (select == 1) {
				//cout << "수도이름 수정\n\n"; //디버깅용
				change();
			}
			else if (select == 2) {
				//cout << "새로운 나라 추가\n\n";
				input();
			}
			else if (select == 3) {
				//cout << "나라 삭제\n\n";
				del();
			}
			else if (select == 4) {
				//cout << "소스파일 백업\n\n";
				backUp();
			}
			else {
				cout << "다시 입력해주세요.\n\n";
			}
		}
		else if (select == 3) {
			cout << "\n[수도정보 검색]\n\n";
			cout << "(1) 나라 이름으로 개별검색 (2) 나라 정보 전체 출력\n";
			cout << "선택: ";
			select = 0;
			cin >> select;
			if (!cin) {
				cout << "잘못된 숫자입력입니다.\n다시 입력해주세요\n\n";
				cin.clear();      //상태플러그 초기화
				cin.ignore(INT_MAX, '\n');      //버퍼값 한꺼번에 지우기
			}
			else if (select == 1) {
				//cout << "나라 이름으로 개별검색\n\n";
				search();
			}
			else if (select == 2) {
				//cout << "나라 정보 전체 출력\n\n";
				show();
			}
				
		}
		else if (select == 4) {
			//cout << "퀴즈\n\n";
			quiz();
		}
		else if (select == 5) {
			return 0;
		}
		else
			cout << "다시 입력해주세요.\n\n";
	}
}

void NationGame::sourceUpload() {
	Nation mNation; 
	string line; 
	string nation;
	string capital;
	int indexSplit;

	ifstream fin("nation.txt"); 

	if (!fin) // 파일 읽기 실패
		cout << "\n파일 읽기 실패\n";

	else { // 파일 읽기 성공
		while (getline(fin, line)) { // 한 줄씩 읽기
			indexSplit = line.find(';'); // ; 기준으로 나누기
			nation = line.substr(0, indexSplit); // 나라
			capital = line.substr(indexSplit + 1, line.length()); // 수도
			mNation.set(nation, capital); // 나라 수도 세팅
			v.push_back(mNation);
		}
		cout << "\n성공적으로 파일을 읽었습니다.\n";
	}
	fin.close();
}
void NationGame::change() {
	vector<Nation>::iterator it;
	string name; // 사용자 입력 변수
	cout << "\n변경할 나라를 입력하세요: ";
	cin >> name;
	for (it = v.begin(); it != v.end(); it++) { //첫 번째부터 조회
		Nation mNation = *it;
		if (mNation.getNation() == name) { 
			cin.clear();
			cin.ignore();
			cout << "\n";
			cout << "변경할 수도의 이름을 입력하세요 : ";
			cin >> name;
			(*it).setCapital(name); // 바뀐 수도 이름 설정
			cout << "\n성공적으로 변경되었습니다.\n";
			break;
		}
	}
	if (it == v.end()) { // 입력한 나라가 없다면
		cout << "\n해당 나라가 존재하지 않습니다.\n";
	}
}
void NationGame::input() {
	vector<Nation>::iterator it;
	Nation myNation;
	string nation;	//중복여부를 비교하기 위해 
	cout << "현재 " << v.size() << "개의 나라가 입력되어 있습니다.\n";
	while (true) {
		cout << "\n";
		cin >> myNation; // 연산자 재정의
		nation = myNation.getNation();
		if (nation == "no") 
			break; 
		else { 
			for (it = v.begin(); it != v.end(); it++) { 
				Nation mmNation = *it;
				if (mmNation.getNation() == nation) 
					break;
			}
			if (it == v.end()) { // 입력한 나라가 없다면
				v.push_back(myNation); 
				cout << "등록 완료!\n";
			}
			else { // 나라 중복의 경우
				cout << "이미 목록에 존재합니다.\n"; 
				continue;
			}
		}
	}
}
void NationGame::del() {
	vector<Nation>::iterator it; 
	string nation;
	bool check = false; // 기존처럼 it == v.end()로 마지막인지 검사하면, 마지막 원소 삭제시 문제됨. 따라서 check로 변경
	cout << "\n삭제할 나라의 이름을 입력하세요.\n";
	cin >> nation;
	for (it = v.begin(); it != v.end(); it++) { 
		Nation mNation = *it;
		if (mNation.getNation() == nation) { 
			it = v.erase(it);
			cout << "\n삭제 완료!\n";
			check = true; // check를 true로 변경, 즉 마지막 위치가 아니다.
			break;
		}
	}
	if (!check) {
		cout << "\n해당 나라가 없습니다...\n";
	}
}
void NationGame::backUp() {
	vector<Nation>::iterator it;
	ofstream fout("nation.txt");
	if (!fout) // 파일 생성 실패
		cout << "\n파일 쓰기에 실패하였습니다.\n";
	else {
		for (it = v.begin(); it != v.end(); it++) 
			fout << (*it).getNation() << ';' << (*it).getCapital() << "\n"; 
		cout << "\n성공적으로 파일을 기록하였습니다\n\n";
	}
	fout.close(); 
}
void NationGame::search() {
	vector<Nation>::iterator it;
	string nation;
	
	cout << "찾을 나라의 이름을 입력하세요.\n";
	cin >> nation;
	for (it = v.begin(); it != v.end(); it++) { 
		Nation mNation = *it;
		if (mNation.getNation() == nation) { 
			cout << endl;
			cout << mNation; 
			break;
		}
	}
	if (it == v.end()) {
		cout << "\n해당 나라가 없습니다...\n";
	}
}
void NationGame::show() {
	vector<Nation>::iterator it; // Nation Vector에 대한 iterator 변수 생성
	int num = 1;
	for (it = v.begin(); it != v.end(); it++) { // 순차 조회하며 출력
		cout << (*it).getNation();
		cout << " - " << (*it).getCapital() << endl;
		num++;
	}

}
void NationGame::quiz() {
	srand(time(NULL));
	int index; 
	correctRate = 0;
	int indexRand;
	string bogiA; //답
	string bogi1; 
	string bogi2; 
	string bogi3; 
	int answer; 

	while (true) {
		index = rand() % v.size();
		bogiA = v[index].getCapital(); 
		bogi1 = v[(index + 5) % v.size()].getCapital(); 
		bogi2 = v[(index + 10) % v.size()].getCapital(); 
		bogi3 = v[(index + 15) % v.size()].getCapital(); 
		indexRand = (rand() % 4) + 1;

		cout << v[index].getNation() << "의 수도는?\n";
		switch (indexRand) { // 정답 보기 1~4
		case 1: { // 정답보기가 1번인 경우
			cout << "(1) " << bogiA << endl;
			cout << "(2) " << bogi1 << endl;
			cout << "(3) " << bogi2 << endl;
			cout << "(4) " << bogi3 << endl;
			break;
		}
		case 2: { // 정답보기가 2번인 경우
			cout << "(1) " << bogi1 << endl;
			cout << "(2) " << bogiA << endl;
			cout << "(3) " << bogi2 << endl;
			cout << "(4) " << bogi3 << endl;
			break;
		}
		case 3: { // 정답보기가 3번인 경우
			cout << "(1) " << bogi1 << endl;
			cout << "(2) " << bogi2 << endl;
			cout << "(3) " << bogiA << endl;
			cout << "(4) " << bogi3 << endl;
			break;
		}
		case 4: { // 정답보기가 4번인 경우
			cout << "(1) " << bogi1 << endl;
			cout << "(2) " << bogi2 << endl;
			cout << "(3) " << bogi3 << endl;
			cout << "(4) " << bogiA << endl;
			break;
		}
		default:
			break;
		}
		cin >> answer;

		if (answer == 9) {	//퀴즈 끝내기
			if (getQuizNum() == 0) {
				cout << "정답률 : 0%\n\n";
				return;
			}
			else {
				setCorrectRate((getRightNum() / getQuizNum()) * 100);
				cout << "전체 문제 수 : " << getQuizNum() << "\n";
				cout << "맞은 문제 수 : " << getRightNum() << "\n";
				cout << "정답률 : " << getCorrectRate() << "%\n\n";
				return;
			}
			
		}
		if (answer == indexRand) {		//정답
			cout << "정답입니다~\n\n";
			setRightNum(getRightNum() + 1);
			//cout << "정답 카운트 : " << getRightNum() << "\n";	//디버깅용
		}
		else {	//오답
			cout << "땡!!!!\n\n";
		}
		setQuizNum(getQuizNum() + 1);
		//cout << "퀴즈 카운트 : " << getQuizNum() << "\n";	//디버깅용
	}
}

int main() {
	NationGame n;
	n.gameStart();
	return 0;
}

