#include <iostream>
using namespace std;

class BankAcct {
	double money;
	double rate;
public:
	//double getMoney() { return money; }
	BankAcct(double m, double rate) { money = m; this->rate = rate; }
	void deposit(double m) { money += m; }
	void withdraw(double m) { money -= m; }
	double getInterest() { return money * rate; }
	virtual void print() {	//프린트 가상함수
		cout << "예금액 : " << money << endl;
		cout << "이자액 : " << getInterest() << endl;
	}
	virtual ~BankAcct() {}	//가상소멸자
};

class SavingAcct : public BankAcct {
public:
	SavingAcct(int m) : BankAcct(m, 0.09) {};
	void print() {	//프린트 가상함수
		cout << "==================" << endl;
		cout << " 저축 예금 계좌" << endl;
		cout << "==================" << endl;
		BankAcct::print();
	}
	virtual ~SavingAcct() {}
};

class CheckingAcct : public BankAcct {
public:
	CheckingAcct(int m) : BankAcct(m, 0.05) {}
	void print() {	//프린트 가상함수
		cout << "==================" << endl;
		cout << " 당좌 예금 계좌" << endl;
		cout << "==================" << endl;
		BankAcct::print();
	}
	virtual ~CheckingAcct() {} //가상소멸자
};

int main()
{
	BankAcct* bank[] = { new SavingAcct(5000000), new CheckingAcct(10000000) };	//동적할당

	bank[0]->deposit(100000);
	bank[1]->deposit(150000);
	
	for (BankAcct* element : bank)
		element->withdraw(500000);

	for (BankAcct* element : bank)
		element->print();

	for (BankAcct* element : bank)	//0번째부터 순서대로 동적할당 해제
		delete element;
	return 0;

}
