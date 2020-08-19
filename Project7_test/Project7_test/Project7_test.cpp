#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

class Nation {
	string nation; // 나라이름 변수
	string capital; // 수도이름 변수
public:
	string getNationName() { return nation; } // 나라 이름을 반환하는 함수
	string getCapitalName() { return capital; } // 수도 이름을 반환하는 함수
	const void setNation(string& n, string& c) { nation = n, capital = c; } // 나라의 이름과 수도를 설정하는 함수
	const void setNationName(string& n) { nation = n; } // 나라 이름을 설정하는 함수
	const void setCapitalName(string& c) { capital = c; } // 수도 이름을 설정하는 함수
	friend istream& operator>>(istream& ins, Nation& n); // Nation 클래스를 위해 재정의한 대입 연산자
	friend ostream& operator<<(ostream& outs, Nation& n); // Nation 클래스를 위해 재정의한 출력 연산자
};

class NationManager {
	vector<Nation> v; // Nation의 Vector 변수 v
	bool menuFlag; // 메뉴의 1번이 실행되었는지를 판단하는 flag 변수
public:
	NationManager() { menuFlag = false; } // 최초 NationManager 클래스를 생성시 menuFlag를 false로 초기화
	const void mainMenu(); // 메인 실행 메뉴를 실행하기 위한 함수
	int updateInfoMenu(); // 2번 메뉴에 해당하는 입력값을 반환하기 위한 함수
	int capitalInfoSearchMenu(); // 3번 메뉴에 해당하는 입력값을 반환하기 위한 함수
	const void sourceFileUpload(); // 1번 메뉴에 해당하는 파일 읽어오기를 실행하기 위한 함수
	const void changeCapitalName(); // 2-1번 메뉴에 해당하는 수도이름을 수정하는 함수
	const void addNewNation(); // 2-2번 메뉴에 해당하는 새로운 나라를 추가하는 함수
	const void deleteNation(); // 2-3번 메뉴에 해당하는 나라를 삭제하는 함수
	const void backupSourceFile(); // 2-4번 메뉴에 해당하는 소스파일을 백업하는 함수
	const void searchNationIndiv(); // 3-1번 메뉴에 해당하는 나라이름으로 개별 검색을 진행하는 함수
	const void showAll(); // 3-2번 메뉴에 해당하는 나라정보 전체 출력을 위한 함수
	const void quiz(); // 4번 메뉴에 해당하는 퀴즈 게임을 위한 함수
};

void clean() { // 키를 하나 입력받아 화면을 지워주는 함수
	cin.ignore(); // 버퍼 비우기
	getchar(); // 키를 하나 입력받음
	system("cls"); // 화면을 지움
}

istream& operator>>(istream& ins, Nation& n) { // Nation 클래스를 위해 재정의한 대입 연산자
	cout << "새로운 나라의 이름을 입력하세요 : ";
	ins >> n.nation; // 입력된 Nation 객체의 nation에 입력값 저장
	cout << "새로운 나라의 수도 이름을 입력하세요 : ";
	ins >> n.capital; // 입력된 Nation 객체의 capital에 입력값 저장
	return ins;
}

ostream& operator<<(ostream& outs, Nation& n) { // Nation 클래스를 위해 재정의한 출력 연산자
	outs << "나라의 이름: " << n.nation << endl; // Nation 객체의 nation을 출력
	outs << "수도의 이름: " << n.capital << endl; // Nation 객체의 capital을 출력
	return outs;
}

const void NationManager::sourceFileUpload() { // 1번 메뉴에 해당하는 파일 읽어오기를 실행하기 위한 함수
	Nation mNation; // Nation 객체
	string line; // 파일의 한 줄을 읽기위한 변수
	string nation; // 나라의 이름 저장
	string capital; // 수도의 이름 저장
	int splitIdx; // ';' 문자를 구분하기 위한 인덱스 위치

	ifstream fin("nation.txt"); // txt파일을 읽어들인다. 이 때 txt파일은 ANSI로 코딩되어 있다.

	if (!fin) // 파일 읽기를 실패한다면, 에러 메시지를 출력한다.
		cout << "\n파일 읽기 에러 발생" << endl;

	else { // 파일 읽기가 성공했다면, 정상적인 절차를 수행한다.
		while (getline(fin, line)) { // 한줄씩 파일을 읽어들임
			splitIdx = line.find(';'); // ';' 문자를 기준으로 나라와 수도를 나누어야 하므로 인덱스를 찾는다.
			nation = line.substr(0, splitIdx); // substr를 이용하여 읽어들인 line의 나라부분을 구분한다.
			capital = line.substr(splitIdx + 1, line.length()); // substr를 이용하여 line의 수도부분을 구분한다.
			mNation.setNation(nation, capital); // Nation 객체에 나라와 수도를 세팅한다.
			v.push_back(mNation); // vector에 push_back 하여 삽입한다.
		}
		cout << endl;
		cout << "성공적으로 파일을 읽었습니다." << endl; // 성공 메세지 출력
	}

	fin.close(); // 파일을 닫아준다.

	clean(); // 화면 정리
}

const void NationManager::changeCapitalName() { // 2-1번 메뉴에 해당하는 수도이름을 수정하는 함수
	vector<Nation>::iterator it; // Nation Vector에 대한 iterator 변수 생성
	string name; // 사용자 입력 변수
	cout << endl;
	cout << "수도를 변경할 나라의 이름을 입력하세요 : ";
	cin >> name;
	for (it = v.begin(); it != v.end(); it++) { // it을 통해 v를 순차조회
		Nation mNation = *it; // mNation에 객체 할당
		if (mNation.getNationName() == name) { // 사용자의 입력과 같으면
			cin.clear();
			cin.ignore();
			cout << endl;
			cout << "\"" << name << "\"(이/가) 검색되었습니다." << endl;
			cout << "변경할 수도의 이름을 입력하세요 : "; // 사용자로부터 변경할 이름을 받는다.
			cin >> name;
			(*it).setCapitalName(name); // 바뀐 수도 이름을 설정

			cout << endl;
			cout << "나라: " << (*it).getNationName() << endl;
			cout << "수도: " << (*it).getCapitalName() << endl;
			cout << endl;
			cout << "성공적으로 변경되었습니다." << endl;

			break;
		}
	}
	if (it == v.end()) { // 만일 함수를 최종까지 조회하여도 발견되지 않으면
		cout << endl;
		cout << "해당 나라가 존재하지 않습니다." << endl; // 오류메세지 출력

	}
	clean(); // 화면 정리
}

const void NationManager::addNewNation() { // 2-2번 메뉴에 해당하는 새로운 나라를 추가하는 함수
	vector<Nation>::iterator it; // Nation Vector에 대한 iterator 변수 생성
	Nation mNation;
	string name;
	cout << endl;
	cout << "-----추가 취소를 원하시면 나라 이름에 no를 넣어주세요-----" << endl;
	while (true) { // while문을 통해 사용자가 취소하기 전까지 국가를 계속 추가
		cout << endl;
		cin >> mNation; // 연산자 재정의를 통해 객체에 입력값 입력
		name = mNation.getNationName();
		if (name == "no") // 만일 입력받은 nation 부분이 no라면, 즉 사용자가 취소입력을 주었다면
			break; // 무한루프를 빠져나가며 종료
		else { // 사용자가 입력을 원하는 경우
			for (it = v.begin(); it != v.end(); it++) { // iterator를 통해 vector를 순차조회
				Nation mmNation = *it; // 객체에 할당
				if (mmNation.getNationName() == name) // 이미 나라가 존재하면
					break; // 무한루프를 빠져나감
			}
			if (it == v.end()) { // 만일 마지막까지 조회하였는데도 발견되지 않으면, 즉, 추가 가능하다면
				v.push_back(mNation); // vector에 새로 객체를 넣어준다.
				cout << "성공적으로 등록되었습니다!" << endl;
			}
			else { // 만일 마지막까지 조회 전에 빠져나온거라면
				cout << name << "(은/는) 이미 목록에 존재합니다." << endl; // 이미 존재한다는 메세지를 띄워줌
				continue; // 계속 진행
			}
		}
	}
	cout << endl;
	cout << "새로운 나라 추가가 종료됩니다." << endl;
	clean(); // 화면 정리
}

const void NationManager::deleteNation() {
	vector<Nation>::iterator it; // Nation Vector에 대한 iterator 변수 생성
	string name;
	bool flag = false; // 기존처럼 it == v.end()로 마지막인지 검사하면, 마지막 원소 삭제시 문제됨. 따라서 flag로 변경
	cout << endl;
	cout << "삭제할 나라의 이름을 입력하세요 : ";
	cin >> name;
	for (it = v.begin(); it != v.end(); it++) { // iterator를 통해 vector를 순차조회
		Nation mNation = *it;
		if (mNation.getNationName() == name) { // 만일 삭제할 이름이 있다면
			it = v.erase(it); // it을 통해 vector에서 제거
			cout << endl;
			cout << name << "이 성공적으로 삭제되었습니다." << endl;
			flag = true; // flag를 true로 변경, 즉 마지막 위치가 아니다.
			break;
		}
	}
	if (!flag) {
		cout << endl;
		cout << "해당 나라가 존재하지 않습니다." << endl;
	}
	clean();
}

const void NationManager::backupSourceFile() {
	vector<Nation>::iterator it; // Nation Vector에 대한 iterator 변수 생성
	ofstream fout("nation.txt"); // fout 객체로 파일생성
	cout << endl;
	if (!fout) // 파일 생성 실패
		cout << "파일 쓰기에 실패하였습니다." << endl;
	else {
		for (it = v.begin(); it != v.end(); it++) // iterator를 통해 vector를 순차조회
			fout << (*it).getNationName() << ';' << (*it).getCapitalName() << endl; // 국가;수도 순으로 파일에 쓴다.
		cout << "성공적으로 파일을 기록하였습니다." << endl;
	}

	fout.close(); // 파일 닫아줌
	clean();
}

const void NationManager::searchNationIndiv() {
	vector<Nation>::iterator it; // Nation Vector에 대한 iterator 변수 생성
	string name;
	cout << endl;
	cout << "찾을 나라의 이름을 입력하세요 : ";
	cin >> name;
	for (it = v.begin(); it != v.end(); it++) { // iterator를 통해 vector를 순차조회
		Nation mNation = *it;
		if (mNation.getNationName() == name) { // 이름을 찾으면
			cout << endl;
			cout << "\"" << name << "\"(이/가) 검색되었습니다." << endl;
			cout << endl;
			cout << mNation; // 재정의한 출력 연산자를 통해 Nation 객체를 출력한다.
			break;
		}
	}
	if (it == v.end()) { // 마지막 까지 조회해도 나오지 않으면
		cout << endl;
		cout << "해당 나라가 존재하지 않습니다." << endl;
	}
	clean();
}

int NationManager::updateInfoMenu() {
	int user_choice; // 사용자 선택 변수
	system("cls");
	while (true) {
		cout << "[2] 정보 갱신" << endl;
		cout << "   (1) 수도이름 수정" << endl;
		cout << "   (2) 새로운 나라 추가" << endl;
		cout << "   (3) 나라 삭제" << endl;
		cout << "   (4) 소스파일 백업" << endl;

		cout << "메뉴 선택 : ";

		cin >> user_choice;
		if (!cin) { // 숫자가 아닌 이상한 입력의 경우
			cout << endl;
			cout << "다시 입력해주세요" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			getchar();
			system("cls");
		}
		else {
			if (user_choice >= 1 && user_choice <= 4) // 메뉴의 1~4번에 해당하는 경우에는 그 값을 반환하기 위해 break
				break;
			else {
				cout << endl;
				cout << "다시 입력해주세요" << endl;
				clean();
			}
		}
	}

	return user_choice;
}

int NationManager::capitalInfoSearchMenu() {
	int user_choice; // 사용자 선택 변수
	system("cls");
	while (true) {
		cout << "[3] 수도정보 검색" << endl;
		cout << "   (1) 나라이름으로 개별 검색" << endl;
		cout << "   (2) 나라정보 전체 출력" << endl;
		cout << "메뉴 선택 : ";

		cin >> user_choice;
		if (!cin) {
			cout << endl;
			cout << "다시 입력해주세요" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			getchar();
			system("cls");
		}
		else {
			if (user_choice >= 1 && user_choice <= 2) // 메뉴의 1~2번에 해당하는 경우에는 그 값을 반환하기 위해 break
				break;
			else {
				cout << endl;
				cout << "다시 입력해주세요" << endl;
				clean();
			}
		}
	}

	return user_choice;
}

const void NationManager::showAll() {
	vector<Nation>::iterator it; // Nation Vector에 대한 iterator 변수 생성
	int count = 1;
	for (it = v.begin(); it != v.end(); it++) { // 순차 조회하며 출력
		cout << setw(3) << setfill(' ') << count; // setw와 setfill을 통해 출력 형식을 정형화
		cout << "| 나라: " << (*it).getNationName() << endl;
		cout << "   | 수도: " << (*it).getCapitalName() << endl;
		count++;
	}
	clean();
}

const void NationManager::quiz() {
	int prob_size = v.size(); // 전체 문제의 크기 즉, vector에 들어있는 목록의 갯수
	int prob_count = 0; // 전체 문제의 갯수
	int correct_count = 0; // 맞은 문제의 갯수
	int problem_idx; // 문제의 인덱스
	int random_idx; // 문제 정답의 객관식 보기 번호 1~4중 1개
	string answer_name; // 문제 정답의 이름
	string problem1_name; // 보기 이름 1
	string problem2_name; // 보기 이름 2
	string problem3_name; // 보기 이름 3
	int answer; // 사용자 입력 정답

	srand(time(NULL)); // 시간을 seed로 난수 생성

	system("cls");
	cout << "=====================================" << endl;
	cout << "==============퀴즈 게임==============" << endl;
	cout << "=====================================" << endl;
	while (true) {
		problem_idx = rand() % prob_size; // vector, 즉 목록의 크기만큼 나누어 0 ~ 목록의 마지막 인덱스 까지의 범위로 난수 생성
		answer_name = v[problem_idx].getCapitalName(); // 문제 정답의 이름
		problem1_name = v[(problem_idx + 5) % prob_size].getCapitalName(); // 보기 이름 1
		problem2_name = v[(problem_idx + 10) % prob_size].getCapitalName(); // 보기 이름 2
		problem3_name = v[(problem_idx + 15) % prob_size].getCapitalName(); // 보기 이름 3
		random_idx = (rand() % 4) + 1; // 문제 정답의 객관식 보기 번호 1~4중 1개
		cout << "=====================================" << endl;
		cout << "=게임 종료를 원하시면 9를 입력하세요=" << endl;
		cout << "=====================================" << endl;

		cout << endl;
		cout << prob_count + 1 << "번 문제입니다." << endl;
		cout << v[problem_idx].getNationName() << "의 수도로 알맞은 도시는?" << endl;
		switch (random_idx) { // 정답의 보기가 1~4일 때의 경우를 나누어 출력
		case 1: { // 정답보기가 1번인 경우
			cout << "(1) " << answer_name << endl;
			cout << "(2) " << problem1_name << endl;
			cout << "(3) " << problem2_name << endl;
			cout << "(4) " << problem3_name << endl;
			break;
		}
		case 2: { // 정답보기가 2번인 경우
			cout << "(1) " << problem1_name << endl;
			cout << "(2) " << answer_name << endl;
			cout << "(3) " << problem2_name << endl;
			cout << "(4) " << problem3_name << endl;
			break;
		}
		case 3: { // 정답보기가 3번인 경우
			cout << "(1) " << problem1_name << endl;
			cout << "(2) " << problem2_name << endl;
			cout << "(3) " << answer_name << endl;
			cout << "(4) " << problem3_name << endl;
			break;
		}
		case 4: { // 정답보기가 4번인 경우
			cout << "(1) " << problem1_name << endl;
			cout << "(2) " << problem2_name << endl;
			cout << "(3) " << problem3_name << endl;
			cout << "(4) " << answer_name << endl;
			break;
		}
		default:
			break;
		}
		cout << "정답: ";
		cin >> answer; // 사용자에게 정답을 입력받음

		if (!cin) { // 사용자 입력이 이상한 경우
			cout << endl;
			cout << "다시 입력해주세요" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			getchar();
			system("cls");
			continue;
		}
		else {
			if (answer >= 1 && answer <= 4) {
				if (answer == random_idx) { // 정답을 맞은경우
					cout << endl;
					cout << "정답입니다!" << endl;
					cout << endl;
					correct_count++; // 맞춘 갯수를 증가시킴
				}
				else { // 오답인 경우
					cout << endl;
					cout << "오답입니다!" << endl;
					cout << "정답은 " << random_idx << "번 " << answer_name << "입니다." << endl; // 정답에 해당하는 나라이름, 수도이름을 출력
					cout << endl;
				}
			}
			else if (answer == 9) { // 종료 시퀸스
				cout << endl;
				cout << "퀴즈 게임을 종료합니다." << endl;
				cout << "전체 문제의 수: " << prob_count << endl;
				cout << "맞춘 문제의 수: " << correct_count << endl;

				// 이렇게 두가지 case로 구분하는 이유는, 한게임도 진행하지 않고 바로 종료시에 발생하는 devide by zero 방지하기 위함.
				cout.precision(4); // out의 형태를 4자리로 제한
				if (prob_count != 0) // 문제를 한개라도 풀었다면
					cout << "정답률 : " << ((double)correct_count / prob_count) * 100 << '%' << endl; // 퍼센트 계산
				else // 한문제도 진행을 하지 않았다면
					cout << "정답률 : 0%" << endl; // 0% 출력

				cout << "Enter를 누르면 종료됩니다." << endl;
				clean();
				break;
			}
			else {
				cout << endl;
				cout << "다시 입력해주세요" << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				getchar();
				system("cls");
				continue;
			}
		}

		prob_count++; // 문제 전체의 갯수를 증가
	}

}

const void NationManager::mainMenu() { // 메인 실행 메뉴를 실행하기 위한 함수
	while (true) {
		int user_choice;
		cout << "[1] 소스파일 업로드" << endl;
		cout << "[2] 정보 갱신" << endl;
		cout << "[3] 수도정보 검색" << endl;
		cout << "[4] 퀴즈" << endl;
		cout << "[5] 종료" << endl;

		cout << "메뉴 선택 : ";
		cin >> user_choice;

		if (!cin) { // 사용자 입력이 이상한 경우
			cout << endl;
			cout << "다시 입력해주세요" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			getchar();
			system("cls");
		}
		else {
			if (user_choice >= 1 && user_choice <= 5) { // 사용자 입력이 제대로 1~5인 경우
				switch (user_choice) { // swtch case 문을 이용하여 분리실행
				case 1: { // 사용자 입력이 1인경우
					if (menuFlag) { // 만일 이미 파일을 불러왔던 경우
						cout << endl;
						cout << "이미 파일을 불러왔습니다." << endl;

						clean();
					}
					else { // 최초 실행이라면
						sourceFileUpload(); // 1번 메뉴에 해당하는 파일 읽어오기를 실행
						menuFlag = true; // menuFlag를 1로 변경하여 파일 업로드가 완료되었음을 표시
					}
					break;
				}
				case 2: { // 사용자 입력이 2인경우
					if (!menuFlag) { // 아직 1번 메뉴를 실행하지 않았다면
						cout << endl;
						cout << "먼저 [1] 소스파일 업로드를 진행해 주세요." << endl;
						clean();
					}
					else { // 1번 메뉴를 실행한 후라면 
						int choice;
						choice = updateInfoMenu(); // 2번 메뉴에 필요한 사용자 입력을 받는 함수 실행
						switch (choice) {
						case 1: {
							changeCapitalName(); // 2-1번 메뉴에 해당하는 수도이름을 수정하는 함수 실행
							break;
						}
						case 2: {
							addNewNation(); // 2-2번 메뉴에 해당하는 새로운 나라를 추가하는 함수 실행
							break;
						}
						case 3: {
							deleteNation(); // 2-3번 메뉴에 해당하는 나라를 삭제하는 함수 실행
							break;
						}
						case 4: {
							backupSourceFile(); // 2-4번 메뉴에 해당하는 소스파일을 백업하는 함수 실행
							break;
						}
						default:
							break;
						}
					}
					break;
				}
				case 3: { // 사용자 입력이 3인경우
					if (!menuFlag) { // 아직 1번 메뉴를 실행하지 않았다면
						cout << endl;
						cout << "먼저 [1] 소스파일 업로드를 진행해 주세요." << endl;
						clean();
					}
					else { // 1번 메뉴를 실행한 후라면 
						int choice;
						choice = capitalInfoSearchMenu();  // 3번 메뉴에 필요한 사용자 입력을 받는 함수 실행
						switch (choice) {
						case 1: {
							searchNationIndiv(); // 3-1번 메뉴에 해당하는 나라이름으로 개별 검색을 진행하는 함수 실행
							break;
						}
						case 2: {
							showAll(); // 3-2번 메뉴에 해당하는 나라정보 전체 출력을 위한 함수 실행
							break;
						}
						default:
							break;
						}
					}
					break;
				}
				case 4: { // 사용자 입력이 4인경우
					if (!menuFlag) { // 아직 1번 메뉴를 실행하지 않았다면
						cout << endl;
						cout << "먼저 [1] 소스파일 업로드를 진행해 주세요." << endl;
						clean();
					}
					else { // 1번 메뉴를 실행한 후라면 
						quiz(); // 4번 메뉴에 해당하는 퀴즈 게임을 위한 함수
					}
					break;
				}
				case 5: { // 사용자 입력이 5인경우
					cout << endl;
					cout << "종료합니다." << endl;
					exit(1); // 1을 반환하며 종료
				}
				default:
					break;
				}
			}
			else {
				cout << endl;
				cout << "다시 입력해주세요" << endl;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				getchar();
				system("cls");
			}
		}
	}
}

int main() {
	NationManager nm; // NationManager 객체 생성
	nm.mainMenu(); // 메인 메뉴 실행
	return 0;
}