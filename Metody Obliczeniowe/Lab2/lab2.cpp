#include <iostream>
#include <math.h>
#include <fstream>
using namespace std;
double epsilon = 2.22045e-16;

double func(double x){
	return (1 - exp(-x))/x;
}

double taylor(double x) {

    double elem = 1.0;
    double sum = 0.0;
    int i = 1;

    while(fabs(elem) >= epsilon) {
        sum += elem;
        elem *= (-x)/ (1 + i);
        i++;
        if(sum > 1E307 || sum != sum) {
            return 1E307;
        }
    }

    return sum;
}

int main() {
	fstream fileIn("data.txt", ios_base::in);
	fstream fileOut("out.txt", ios_base::out); 
	double x, log, fx;
	int i = 0;
	/////////////////////METODA 1/////////////////////
	
	while (!fileIn.eof()){
		fileIn >> log;
		fileIn >> x;
		fileIn >> fx;
		double result = func(x);
		double error = abs((result - fx)/fx);
		
		fileOut << x << "\t";
fileOut << result << "\t";		
		fileOut << error << "\n";
		
		
	}
	//////////////////////METODA 2///////////////
	fstream fileIn2("data.txt", ios_base::in);
	fstream fileOut2("out2.txt", ios_base::out);
int h = 0;	
	while (!fileIn2.eof()){
		fileIn2 >> log;
		fileIn2 >> x;
		fileIn2 >> fx;
		double result1 = func(x);
		double error1 = abs((result1 - fx)/fx);
		
		double result2 = taylor(x);
		double error2 = abs((result2 - fx)/fx);
		
		if(error1 > error2) {
            result1 = result2;
            error1 = error2;
        }
		if (h % 100 == 0){
		fileOut2 << x << "\t";
		fileOut2 << error1 << "\n";
		}
		h++;
	}
	
	return 0;
}