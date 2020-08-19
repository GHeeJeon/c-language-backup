//#include <iostream>
//using namespace std;
//
//#include "exp.h"
//
//int main() {
//	Exp a(3, 2);
//	Exp b(9);
//	Exp c;
//
//	cout << a.getValue() << ' ' << b.getValue() << ' ' << c.getValue() << endl;
//	cout << "a의 베이스 " << a.getBase() << ',' << "지수 " << a.getExp() << endl;
//
//	if (a.equals(b))
//		cout << "same" << endl;
//	else
//		cout << "not same" << endl;
//}
#include <iostream>
using namespace std;
class Point {
private:
	double x, y;
public:
	Point();
	Point(double xx, double yy);
	double getX();
	double getY();
	void setX(double xx);
	void setY(double yy);
	void showPoint();
};
Point::Point() : Point(0, 0) {}
Point::Point(double xx, double yy) : x(xx), y(yy) {}
double Point::getX()
{
	return x;
}
double Point::getY()
{
	return y;
}
void Point::setX(double xx)
{
	x = xx;
}
void Point::setY(double yy)
{
	y = yy;
}
void Point::showPoint()
{
	cout << "( " << x << ", " << y << " )\n";
}
int main()
{
	Point p1(1, 7), p2(1, 1);
	p1.showPoint();
	p2.showPoint();
}

