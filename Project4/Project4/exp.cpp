//#include "exp.h"
//
//Exp::Exp(int b, int e) {
//	base = b; exp = e;
//}
//
//Exp::Exp(int b) {
//	base = b; exp = 1;
//}
//
//Exp::Exp() {
//	base = 1; exp = 1;
//}
//
//int Exp::getValue() {
//	int n = 1;
//	for (int i = 0; i < exp; ++i)
//		n *= base;
//	return n;
//}
//int Exp::getBase() {
//	return base;
//}
//int Exp::getExp() {
//	return exp;
//}
//bool Exp::equals(Exp b) {
//	if (this->getValue() == b.getValue())
//		return true;
//	else
//		return false;
//}