#include <iostream>
#include <math.h>
#include <windows.h>
#include <iomanip>
using namespace std;

double f1(double x, double y, double z) {
	return x*x + y*y + z*z - 2;
}

double f2(double x, double y) {
	return x*x + y*y - 1;
}

double f3(double x, double y) {
	return x*x - y;
}

double wyznacznik(double m[][3]) {
	return m[0][2] * m[1][1] * m[2][0] - m[1][0] * m[2][1] * m[0][2];
}

double solve(double *value, double TOLX, double TOLF, int iter) {
	double funcValue[3];
	double jacobian[3][3];
	double value_new[3];
	double var_H[3];
	cout << "| i |      x        |        y        |       z        |" << endl;
	
	for (int i = 0; i < iter; i++) {
		
		//obliczanie wartosci funkcji dla aktualnych przyblizen
		funcValue[0] = f1(value[0], value[1], value[2]);
		funcValue[1] = f2(value[0], value[1]);
		funcValue[2] = f3(value[0], value[1]);
		
		//tworznie macierzy Jacobiego
		jacobian[0][0] = 2 * value[0];
		jacobian[0][1] = 2 * value[1];
		jacobian[0][2] = 2 * value[2];
		jacobian[1][0] = 2 * value[0];
		jacobian[1][1] = 2 * value[1];
		jacobian[1][2] = 0;
		jacobian[2][0] = 2 * value[0];
		jacobian[2][1] = -1;
		jacobian[2][2] = 0;
			
		double w = wyznacznik(jacobian);
				 
		var_H[0] = (jacobian[0][0] * funcValue[0] + jacobian[0][1] * funcValue[1] + jacobian[0][2] * funcValue[2]) / w;
		var_H[1] = (jacobian[1][0] * funcValue[0] + jacobian[1][1] * funcValue[1] + jacobian[1][2] * funcValue[2]) / w;
		var_H[2] = (jacobian[2][0] * funcValue[0] + jacobian[2][1] * funcValue[1] + jacobian[2][2] * funcValue[2]) / w;	
		
		//obliczanie nowej wartosci przyblizonej
		value_new[0] = value[0] - var_H[0];
		value_new[1] = value[1] - var_H[1];
		value_new[2] = value[2] - var_H[2];
		
		//kryteria zakonczenia iteracji TOLX i TOLF
		bool flag = false;
		for (int i = 0; i < 3; i++)
			if (fabs(value[i] - value_new[i]) < TOLX){
				flag = true;
				break;
			}
		if (flag) break;
		
		if (fabs(funcValue[0] - f1(value_new[0], value_new[1], value_new[2])) < TOLF)
			break;
		if (fabs(funcValue[1] - f2(value_new[0], value_new[1])) < TOLF)
			break;
		if (fabs(funcValue[2] - f3(value_new[0], value_new[1])) < TOLF)
			break;
		
		for (int i = 0; i < 3; i++)
			value[i] = value_new[i];
		
		//wypisanie aktualnych przyblizonych wartosci
		cout << "| " << i << " | " << value[0] << "  |  " << value[1] << "  |  " << value[2] << " |" << endl;
	}
	
}

int main(){
	cout.setf(ios::scientific);
	double eps = 0.00000001;
	double v[3] = {1.4, 0.3, 0.4};
	solve(v, eps, eps, 100);
	
}