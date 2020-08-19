#include <iostream>

using namespace std;

class Circle {
	int radius;
	char* color;
	static int count;
public:
	void setRadius(int r) { radius = r; }
	static int getCount() { return count; }
	int getRadius() { return radius; }
	int getArea();
	int getPerimeter();
	void print();
	friend bool is_equal(Circle& c1, Circle& c2);
	
	Circle() {
		radius = 0;
		color = nullptr;
		count++;
		cout << "생성자 (" << radius << ")" << endl;
	}

	Circle(int radius) {
		this->radius = radius;
		color = nullptr;
		count += 1;
		cout << "생성자 (" << radius << ")" << endl;
	}

	Circle(int radius, const char* color) {
		int len = strlen(color);
		this->radius = radius;
		this->color = new char(len + 1);
		strcpy(this->color, color);
		count += 1;
		cout << "생성자 (" << radius << ")" << endl;
	}

	~Circle() {
		count -= 1;
		cout << "소멸자 (" << radius << ")" << endl;
	}

	Circle(const Circle& c) {// 복사생성자
		int len = strlen(c.color);
		radius = c.radius;
		color = new char(len + 1);
		strcpy(color, c.color);
		count += 1;
		cout << "복사 생성자 (" << radius << ")" << endl;
	} 

	Circle& operator=(const Circle& op2) {// 복사대입연산자
		delete[] this->color;
		radius = op2.radius;
		color = new char(strlen(op2.color) + 1);
		strcpy(color, op2.color);
		cout << "복사 대입 연산자 (" << radius << ")" << endl;
		return *this;
	} 

	Circle(Circle&& c) {// 이동생성자
		radius = c.radius;
		color = c.color;
		c.color = nullptr;
		count += 1;
		cout << "이동생성자 (" << radius << ")" << endl;
	} 

	Circle& operator=(Circle&& op2) {// 이동대입연산자
		radius = op2.radius;
		cout << "이동대입연산자 (" << radius << ")" << endl;
		return *this;
	}

	Circle operator+(Circle& op2) {// 덧셈연산자
		Circle tmp;
		tmp.radius = radius + op2.getRadius();
		tmp.color = new char(10);
		strcpy(tmp.color, "chagned");
		return tmp;
	} 
};

int Circle::count = 0;

void Circle::print() {
	int length = strlen(color);
	cout << "원의 색깔: ";
	for (int i = 0; i < length; i++)
		cout << *(color + i);
	cout << endl;
	cout << "원의 개수: " << count << endl;

}

int Circle::getArea() {
	return radius * radius * 3.14;
}

int Circle::getPerimeter() {
	return 2 * 3.14 * radius;
}

bool is_equal(Circle& c1, Circle& c2) {
	if (c1.radius == c2.radius &&
		!strcmp(c1.color, c2.color))
		return true;
	else return false;
}

int main() {

	Circle blackC(10, "Black");
	Circle whiteC(20, "White");

	Circle copy(blackC);
	copy.print();

	Circle c0, c1;
	c0 = whiteC;
	c1 = c0 + blackC;
	if (is_equal(whiteC, blackC) == true)
		cout << "원 일치." << endl;
	else
		cout << "원 불일치." << endl;
	

	return 0;

}