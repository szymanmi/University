#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
#include <fstream>
#include <string>
#include <typeinfo>

using namespace std;

double KR = 0.1;
const int I_KR = 20;
const int I_M = 7;

template <typename T> T f(T x)
{
	return cos(x / 2);
}

template <typename T> T r_prog(T x, T h)
{
	return (f(x + h) - f(x)) / h;
}

template <typename T> T r_wste(T x, T h)
{
	return (f(x) - f(x - h)) / h;
}

template <typename T> T r_cent(T x, T h)
{
	return (f(x + h) - f(x - h)) / (2.0 * h);
}

template <typename T> T r_prog_3pkt(T x, T h)
{
	return (4.0 * f(x + h) - (3.0 * f(x) + f(x + 2.0 * h))) / (2.0 * h);
}

template <typename T> T r_wste_3pkt(T x, T h)
{
	return (f(x - 2.0 * h) - 4.0 * f(x - h) + 3.0 * f(x)) / (2.0 * h);
}

template <typename T> T fprim(T x)
{
	return (-0.5 * sin(x / 2.0));
}

template <typename T> void roznica(T *stepi, T **wyniki)
{
	T start = 0.0;
	T cent = M_PI_2;
	T end = M_PI;
	T step = KR;

	for (int i = 0; i < I_KR; i++)
	{
		stepi[i] = step;

		wyniki[0][i] = fabs(fprim(start) - r_prog(start, step));
		wyniki[1][i] = fabs(fprim(start) - r_prog_3pkt(start, step));

		wyniki[2][i] = fabs(fprim(cent) - r_wste(cent, step));
		wyniki[3][i] = fabs(fprim(cent) - r_cent(cent, step));
		wyniki[4][i] = fabs(fprim(cent) - r_prog(cent, step));

		wyniki[5][i] = fabs(fprim(end) - r_wste(end, step));
		wyniki[6][i] = fabs(fprim(end) - r_wste_3pkt(end, step));

		step /= 10;
	}
}

template <typename T> void zapis_do_pliku(T *stepi, T **wyniki, string *opisy)
{
	fstream plik;
	string nazwa = "DANE_";
	nazwa += typeid(T).name();
	nazwa += ".txt";
	plik.open(nazwa.c_str(), fstream::out);
	plik.width(6);
	plik << left << opisy[0];

	for (int i = 1; i < I_M + 1; i++)
	{
		plik.width(13);
		plik << left << opisy[i];
	}

	plik << endl;

	for (int i = 0; i < I_KR; i++)
	{
		plik.width(5);
		plik << left << log10(stepi[i]) << " ";

		for (int j = 0; j < I_M; j++)
		{
			plik.width(12);
			plik << left << log10(wyniki[j][i]) << " ";
		}

		plik << endl;
	}

	plik.close();
}

int main()
{
	float *kr_flt, **wy_flt;
	double *kr_dbl, **wy_dbl;
	string *opisy;

	kr_flt = new float[I_KR];
	kr_dbl = new double[I_KR];
	wy_flt = new float *[I_M];
	wy_dbl = new double *[I_M];

	for (int i = 0; i < I_M; i++)
	{
		wy_flt[i] = new float[I_KR];
		wy_dbl[i] = new double[I_KR];
	}

	opisy = new string[I_M + 1];

	opisy[0] = "step";
	opisy[1] = "PP - P2";
	opisy[2] = "PP - P3";
	opisy[3] = "PS - W2";
	opisy[4] = "PS - C";
	opisy[5] = "PS - P2";
	opisy[6] = "PK - W2";
	opisy[7] = "PK - W3";

	roznica<float>(kr_flt, wy_flt);
	roznica<double>(kr_dbl, wy_dbl);
	
	for(int i = 0; i < 20; i++){
		for (int j = 0; j < 7; j++){
			cout << wy_dbl[j][i] << '\t';
		}
		cout << endl;
	}
	zapis_do_pliku<float>(kr_flt, wy_flt, opisy);
	zapis_do_pliku<double>(kr_dbl, wy_dbl, opisy);

	system("pause");
}