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
	friend istream& operator >> (istream& ins, Nation& n);	//���Կ����� �ߺ�
	friend ostream& operator << (ostream& stream, Nation& n);	//���⿬���� �ߺ�
};

istream& operator>>(istream& ins, Nation& n) { //���� ������
	cout << "���� �Է��ϼ���.(���� �Է°��� no�� �Է³�)\n ";
	ins >> n.nation; 
	if (n.nation == "no")
		return ins;
		
	cout << "���� �̸��� �Է��ϼ���\n";
	ins >> n.capital; 
	return ins;
}

ostream& operator << (ostream& stream, Nation& n) { // ���� ������
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
	cout << "�������! ���� ���߱� ����\n\n";
	for (;;) {
		cout << "-------Menu-------\n";
		cout << "[1] �ҽ����� ���ε�\n"; //txt���� ���ͷ� �޾ƿ���
		cout << "[2] ���� ����\n";
		cout << "[3] �������� �˻�\n";
		cout << "[4] ����\n";
		cout << "[5] ����\n";
		cout << "����: ";
		int select;
		cin >> select;
		if (!cin) {
			cout << "�߸��� �����Է��Դϴ�.\n�ٽ� �Է����ּ���\n\n";
			cin.clear();      //�����÷��� �ʱ�ȭ
			cin.ignore(INT_MAX, '\n');      //���۰� �Ѳ����� �����
		}

		else if (select == 1) {
			sourceUpload();
		}
		else if (select == 2) {
			cout << "\n[���� ����]\n";
			cout << "(1) �����̸� ����  (2) ���ο� ���� �߰�  (3) ���� ����  (4) �ҽ����� ���\n";
			cout << "����: ";
			select = 0;
			cin >> select;
			if (!cin) {
				cout << "�߸��� �����Է��Դϴ�.\n�ٽ� �Է����ּ���\n\n";
				cin.clear();      //�����÷��� �ʱ�ȭ
				cin.ignore(INT_MAX, '\n');      //���۰� �Ѳ����� �����
			}
			else if (select == 1) {
				//cout << "�����̸� ����\n\n"; //������
				change();
			}
			else if (select == 2) {
				//cout << "���ο� ���� �߰�\n\n";
				input();
			}
			else if (select == 3) {
				//cout << "���� ����\n\n";
				del();
			}
			else if (select == 4) {
				//cout << "�ҽ����� ���\n\n";
				backUp();
			}
			else {
				cout << "�ٽ� �Է����ּ���.\n\n";
			}
		}
		else if (select == 3) {
			cout << "\n[�������� �˻�]\n\n";
			cout << "(1) ���� �̸����� �����˻� (2) ���� ���� ��ü ���\n";
			cout << "����: ";
			select = 0;
			cin >> select;
			if (!cin) {
				cout << "�߸��� �����Է��Դϴ�.\n�ٽ� �Է����ּ���\n\n";
				cin.clear();      //�����÷��� �ʱ�ȭ
				cin.ignore(INT_MAX, '\n');      //���۰� �Ѳ����� �����
			}
			else if (select == 1) {
				//cout << "���� �̸����� �����˻�\n\n";
				search();
			}
			else if (select == 2) {
				//cout << "���� ���� ��ü ���\n\n";
				show();
			}
				
		}
		else if (select == 4) {
			//cout << "����\n\n";
			quiz();
		}
		else if (select == 5) {
			return 0;
		}
		else
			cout << "�ٽ� �Է����ּ���.\n\n";
	}
}

void NationGame::sourceUpload() {
	Nation mNation; 
	string line; 
	string nation;
	string capital;
	int indexSplit;

	ifstream fin("nation.txt"); 

	if (!fin) // ���� �б� ����
		cout << "\n���� �б� ����\n";

	else { // ���� �б� ����
		while (getline(fin, line)) { // �� �پ� �б�
			indexSplit = line.find(';'); // ; �������� ������
			nation = line.substr(0, indexSplit); // ����
			capital = line.substr(indexSplit + 1, line.length()); // ����
			mNation.set(nation, capital); // ���� ���� ����
			v.push_back(mNation);
		}
		cout << "\n���������� ������ �о����ϴ�.\n";
	}
	fin.close();
}
void NationGame::change() {
	vector<Nation>::iterator it;
	string name; // ����� �Է� ����
	cout << "\n������ ���� �Է��ϼ���: ";
	cin >> name;
	for (it = v.begin(); it != v.end(); it++) { //ù ��°���� ��ȸ
		Nation mNation = *it;
		if (mNation.getNation() == name) { 
			cin.clear();
			cin.ignore();
			cout << "\n";
			cout << "������ ������ �̸��� �Է��ϼ��� : ";
			cin >> name;
			(*it).setCapital(name); // �ٲ� ���� �̸� ����
			cout << "\n���������� ����Ǿ����ϴ�.\n";
			break;
		}
	}
	if (it == v.end()) { // �Է��� ���� ���ٸ�
		cout << "\n�ش� ���� �������� �ʽ��ϴ�.\n";
	}
}
void NationGame::input() {
	vector<Nation>::iterator it;
	Nation myNation;
	string nation;	//�ߺ����θ� ���ϱ� ���� 
	cout << "���� " << v.size() << "���� ���� �ԷµǾ� �ֽ��ϴ�.\n";
	while (true) {
		cout << "\n";
		cin >> myNation; // ������ ������
		nation = myNation.getNation();
		if (nation == "no") 
			break; 
		else { 
			for (it = v.begin(); it != v.end(); it++) { 
				Nation mmNation = *it;
				if (mmNation.getNation() == nation) 
					break;
			}
			if (it == v.end()) { // �Է��� ���� ���ٸ�
				v.push_back(myNation); 
				cout << "��� �Ϸ�!\n";
			}
			else { // ���� �ߺ��� ���
				cout << "�̹� ��Ͽ� �����մϴ�.\n"; 
				continue;
			}
		}
	}
}
void NationGame::del() {
	vector<Nation>::iterator it; 
	string nation;
	bool check = false; // ����ó�� it == v.end()�� ���������� �˻��ϸ�, ������ ���� ������ ������. ���� check�� ����
	cout << "\n������ ������ �̸��� �Է��ϼ���.\n";
	cin >> nation;
	for (it = v.begin(); it != v.end(); it++) { 
		Nation mNation = *it;
		if (mNation.getNation() == nation) { 
			it = v.erase(it);
			cout << "\n���� �Ϸ�!\n";
			check = true; // check�� true�� ����, �� ������ ��ġ�� �ƴϴ�.
			break;
		}
	}
	if (!check) {
		cout << "\n�ش� ���� �����ϴ�...\n";
	}
}
void NationGame::backUp() {
	vector<Nation>::iterator it;
	ofstream fout("nation.txt");
	if (!fout) // ���� ���� ����
		cout << "\n���� ���⿡ �����Ͽ����ϴ�.\n";
	else {
		for (it = v.begin(); it != v.end(); it++) 
			fout << (*it).getNation() << ';' << (*it).getCapital() << "\n"; 
		cout << "\n���������� ������ ����Ͽ����ϴ�\n\n";
	}
	fout.close(); 
}
void NationGame::search() {
	vector<Nation>::iterator it;
	string nation;
	
	cout << "ã�� ������ �̸��� �Է��ϼ���.\n";
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
		cout << "\n�ش� ���� �����ϴ�...\n";
	}
}
void NationGame::show() {
	vector<Nation>::iterator it; // Nation Vector�� ���� iterator ���� ����
	int num = 1;
	for (it = v.begin(); it != v.end(); it++) { // ���� ��ȸ�ϸ� ���
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
	string bogiA; //��
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

		cout << v[index].getNation() << "�� ������?\n";
		switch (indexRand) { // ���� ���� 1~4
		case 1: { // ���亸�Ⱑ 1���� ���
			cout << "(1) " << bogiA << endl;
			cout << "(2) " << bogi1 << endl;
			cout << "(3) " << bogi2 << endl;
			cout << "(4) " << bogi3 << endl;
			break;
		}
		case 2: { // ���亸�Ⱑ 2���� ���
			cout << "(1) " << bogi1 << endl;
			cout << "(2) " << bogiA << endl;
			cout << "(3) " << bogi2 << endl;
			cout << "(4) " << bogi3 << endl;
			break;
		}
		case 3: { // ���亸�Ⱑ 3���� ���
			cout << "(1) " << bogi1 << endl;
			cout << "(2) " << bogi2 << endl;
			cout << "(3) " << bogiA << endl;
			cout << "(4) " << bogi3 << endl;
			break;
		}
		case 4: { // ���亸�Ⱑ 4���� ���
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

		if (answer == 9) {	//���� ������
			if (getQuizNum() == 0) {
				cout << "����� : 0%\n\n";
				return;
			}
			else {
				setCorrectRate((getRightNum() / getQuizNum()) * 100);
				cout << "��ü ���� �� : " << getQuizNum() << "\n";
				cout << "���� ���� �� : " << getRightNum() << "\n";
				cout << "����� : " << getCorrectRate() << "%\n\n";
				return;
			}
			
		}
		if (answer == indexRand) {		//����
			cout << "�����Դϴ�~\n\n";
			setRightNum(getRightNum() + 1);
			//cout << "���� ī��Ʈ : " << getRightNum() << "\n";	//������
		}
		else {	//����
			cout << "��!!!!\n\n";
		}
		setQuizNum(getQuizNum() + 1);
		//cout << "���� ī��Ʈ : " << getQuizNum() << "\n";	//������
	}
}

int main() {
	NationGame n;
	n.gameStart();
	return 0;
}

