#include <iostream>
#include <math.h>
#include <windows.h>
#include <iomanip>
using namespace std;
typedef double(*func)(double);

//funkcje potrzebne do realizacji zadania
double f1(double x) {
	return sin(x/4)*sin(x/4) - x;
}

double f2(double x) {
	return tan(2*x) - x - 1;
}

//funkcje pochodne
double df1(double x) {
	return (1.0 / 4.0) * (sin(x / 2.0) - 4.0);
}

double df2(double x) {
	return -1.0 + 2.0 / (cos(2.0 * x) * cos(2.0 * x)); 
}

//funkcje dla metody Picarda
double xf1(double x) {
	return sin(x/4)*sin(x/4);
}

double xf2(double x) {
	return tan(2*x) - 1;
}

double bisekcja(func f, double a, double b, double TOLX, double TOLF, int iter) {
	while (f(a) * f(b) > 0){
		cout << "Bledne dane, podaj ponownie\n";
		cin >> a >> b;
	}
	
	double c;
	
	for (int i = 0; i < iter; i++) {
		c = (a+b)/2;
		if (f(a) * f(c) < 0)
			b = c;
		else
			a = c;
		cout << c << endl;
		
		if ((b-a)/2 <= TOLX || fabs(f(c)) <= TOLF) 
			return c;
	}
	return c;
}

double picard(func f, func xf, double x, double TOLX, double TOLF, int iter) {	
	double previous = x;
	for (int i = 0; i < iter; i++){
		x = xf(x);
		cout << x << endl;
		if (fabs(x-previous) <= TOLX || fabs(f(x)) <= TOLF)
			return x;
		previous = x;
	}
	return x;
	
}

double newton(func f, func df, double x, double TOLX, double TOLF, int iter) {
	double previous = x;
	for (int i = 0; i < iter; i++){
		x = x - f(x)/df(x);
		cout << x << endl;
		if(fabs(x-previous) <= TOLX || fabs(f(x)) <= TOLF)
			return x;
		previous = x;
	}
	return x;
}

double sieczne(func f, double x0, double x1, double TOLX, double TOLF, int iter) {
	double x2;
	for (int i = 0; i < iter; i++){
		x2 = x1 - f(x1) / ((f(x1) - f(x0)) / (x1-x0));
		x0 = x1;
		x1 = x2;
		cout << x1 << endl;
		
		if (fabs(x0-x1) <= TOLX || fabs(f(x2)) <= TOLF)
			return x2;
	}
	return x2;
}


int main() {
	cout.setf(ios::scientific);
	double eps = 0.00000000001;
	cout << bisekcja(f1, -10, 11, eps, eps, 300) << endl << endl;
	cout << picard(f1, xf1, 11, eps, eps, 300) << endl << endl;
	cout << newton(f1, df1, 11, eps, eps, 300) << endl << endl;
	cout << sieczne(f1, -0.5, 0.6, eps, eps, 300) << endl << endl << endl;
	
	cout << bisekcja(f2, -0.4, 0.6, eps, eps, 300) << endl << endl;
	cout << newton(f2, df2, 0.6, eps, eps, 300) << endl << endl;
	cout << sieczne(f2, -0.5, 0.6, eps, eps, 300) << endl << endl << endl;
	
	return 0;
}