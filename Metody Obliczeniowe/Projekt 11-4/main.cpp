#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include "calerf.h"

using namespace std;
double EPS = 0.000001; // do SORA
double D = 1.0;
double tmax = 2.0;
double a = 1 + (6 * sqrt(D * tmax));
double lambda = 1;
double h = 0.1;
double dt = (lambda * (h * h) / D);
int N = static_cast<const int>((tmax / dt) + 2); //ilosc poziomow czasowych
int M = static_cast<const int>((a * 2 / h) + 1); //ilosc poziomow przestrz.

void ustaw_zmienne(int m) {
    M = m;
    h = 2 * a / (double) (m);
    dt = (lambda * (h * h) / D);
    N = static_cast<const int>((tmax / dt) + 2);
}

double **nowa_macierz(int n, int m) {
    double **matrix = new double *[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new double[m];
    }
    return matrix;
}

double *new_vector(int n) {
    double *vector = new double[n];
    for (int i = 0; i < n; i++)
        vector[i] = 0;
    return vector;
}

double **mul_2_matrices(double **A, double **B, int n) {
    double **solution = nowa_macierz(n, n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            solution[i][j] = 0;
            for (int k = 0; k < n; k++)
                solution[i][j] += A[i][k] * B[k][j];
        }

    return solution;
}

double *mul_matrix_vector(double **A, double *B, int n) {
    double *solution = new_vector(n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            solution[i] += B[j] * A[i][j];

    return solution;
}

void fill_dt(double *x, double delta, int k) {
    x[0] = 0; // wynika z zalozen
    for (int i = 1; i < k; i++)
        x[i] = x[i - 1] + delta;
}

void fill_h(double *x, double delta, int k) {
    x[0] = -a; // wynika z warunkow poczatkowych
    for (int i = 1; i < k; i++)
        x[i] = x[i - 1] + delta;
}

void zapisz_plik(char *filename, double **matrix, int N, int M, double *h_levels) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Nie moge zapisac: " << filename << " !!!" << endl;
        exit(1);
    }
    file.setf(ios::scientific, ios::floatfield);
    file.precision(4);
    for (int i = 0; i < M; i++) {
        file << endl;
        //1 kolumna to kroki prestrzenne !!!
        ///2 kolumna to log10(kroku_przestrzenneg) !!!
        file << h_levels[i] << "\t";
        //file << log10(h_levels[i]) << "\t";
        for (int j = 0; j < N; j++)
            //file << log10(matrix[j][i]) << "\t";
            file << matrix[j][i] << "\t";
    }
    file.close();
    cout << "Zapisano: " << filename << endl;
}

void zapisz_plik2(char *filename, double *vekt, int r, double *dt_levels, double *h_levels) {

    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Nie moge zapisac: " << filename << " !!!" << endl;
        exit(1);
    }
    file.setf(ios::scientific, ios::floatfield);
    file.precision(4);
    for (int i = 0; i < r; i++)
        // pierwsza kolumna to kroki czasowe !!!
        // 2 - kroki przestrzenne 3 -
        /// 2 - max bledy 3 - (krok_przestrzenny) 4 - log10(maxbledy)
        file << dt_levels[i] << "\t" << h_levels[i] << "\t" << vekt[i] << endl;
    file.close();
    cout << "Zapisano: " << filename << endl;
}

void analityczne(double **ANAL, int N, int M, double *dt_levels, double *h_levels) {
    for (int i = 0; i < N; i++)    //warunek brzegowy U(0,t)=0
        ANAL[i][0] = 0;
    for (int i = 0; i < N; i++)    //warunek brzegowy U(INF,t)=0
        ANAL[i][M - 1] = 0;
    for (int i = 0; i < M; i++)  //warunek poczatkowy  U(x,0)= (1 dla x<0) (1 dla x>=0)
        if (fabs(h_levels[i]) < 1.0)
            ANAL[0][i] = 1.;
        else
            ANAL[0][i] = 0.;

    for (int i = 1; i < N; i++) {
        for (int j = 1; j < M; j++)
            ANAL[i][j] = 0.5 * (erf((h_levels[j] + 1) / (2 * sqrt(D * dt_levels[i])))) -
                         0.5 * (erf((h_levels[j] - 1) / (2 * sqrt(D * dt_levels[i]))));
    }
    zapisz_plik(const_cast<char *>("rozw_analityczne_Lasson.txt"), ANAL, N, M, h_levels);
}

void blad_LU(double **BLAD, double **ANAL, double **U, int N, int M, double *h_levels, double *dt_levels) {
    double *max_blad = new double[N];
    double *bledy_tmax = new double[M];
    for (int i = 0; i < N; i++) max_blad[i] = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            BLAD[i][j] = fabs(U[i][j] - ANAL[i][j]);
            if (max_blad[i] < fabs(U[i][j] - ANAL[i][j])) max_blad[i] = fabs(U[i][j] - ANAL[i][j]);
        }
    }
    zapisz_plik(const_cast<char *>("bledy_Lasson_LU.txt"), BLAD, N, M, h_levels);
    zapisz_plik2(const_cast<char *>("MAXbledy_Lasson_LU.txt"), max_blad, N, dt_levels, h_levels);
}

void blad_od_h(double **ANAL, double **U, int N, int M, double *h_levels, double *dt_levels) {

    double max_blad = 0;
    int max_i = 0;
    for (int j = 0; j < M; j++) {
        double temp = fabs(U[N - 1][j] - ANAL[N - 1][j]);
        if (temp > max_blad) {
            max_blad = temp;
            max_i = j;
        }
    }
    cout.setf(ios::scientific);
    cout << setprecision(8) << log10(h) << '\t' << log10(max_blad) << '\t' << endl;
}

void blad_gaussseidel(double **BLAD, double **ANAL, double **U, int N, int M, double *h_levels, double *dt_levels) {
    double *max_blad = new double[N];
    for (int i = 0; i < N; i++) max_blad[i] = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            BLAD[i][j] = fabs(U[i][j] - ANAL[i][j]);
            if (max_blad[i] < fabs(U[i][j] - ANAL[i][j])) max_blad[i] = fabs(U[i][j] - ANAL[i][j]);
        }
    }
    zapisz_plik(const_cast<char *>("bledy_Lasson_gaussseidel.txt"), BLAD, N, M, h_levels);
    zapisz_plik2(const_cast<char *>("MAXbledy_Lasson_gaussseidel.txt"), max_blad, N, dt_levels, h_levels);
}

double **gauss_jordan(double **A) {
    double **D = nowa_macierz(N, M);
    double **T = nowa_macierz(N, M);
    for (int i = 0; i < M; i++) {
        T[i][i] = 1;
        for (int j = 0; j < M; j++)
            D[i][j] = A[i][j];
    }

    for (int i = 0; i < M; i++) {
        double temp = D[i][i];
        for (int j = 0; j < M; j++) {
            D[i][j] *= 1 / temp;
            T[i][j] *= 1 / temp;
        }


        for (int j = 0; j < M; j++) {
            if (i != j) {
                double temp2 = D[j][i] / D[i][i];
                for (int k = 0; k < M; k++) {
                    D[j][k] -= D[i][k] * temp2;
                    T[j][k] -= temp2 * T[i][k];
                }
            }
        }
    }

    return T;
}

void gauss_seidel(double **A, double B[], double X[]) {
    double **LD = nowa_macierz(M, M);
    double **U = nowa_macierz(M, M);

    for (int i = 0; i < M; i++)
        for (int j = 0; j < M; j++) {
            if (i >= j)
                LD[i][j] = A[i][j];
            else
                U[i][j] = A[i][j];
        }

    LD = gauss_jordan(LD);

    double **M1 = mul_2_matrices(LD, U, M);
    double *C = mul_matrix_vector(LD, B, M);


    for (int iter = 0; iter < 1000; iter++) {
        double *temp = mul_matrix_vector(M1, X, M);
        for (int i = 0; i < M; i++)
            X[i] = C[i] - temp[i];

    }

}

void Lassonen_GaussSeidel(double **U, int n, int m, double *dt_levels, double *h_levels) {
    double *x = new double[M];
    double *b = new double[M];
    double **WSP = new double *[M];
    for (int i = 0; i < M; i++)
        WSP[i] = new double[M];

    for (int i = 0; i < M; i++)
        for (int j = 0; j < M; j++)
            WSP[i][j] = 0;


    for (int i = 0; i < N; i++)    //warunek brzegowy Xm
        U[i][0] = 0.;
    for (int i = 0; i < N; i++)    //warunek brzegowy X0
        U[i][M - 1] = 0.;
    for (int i = 0; i < M; i++)  //warunek poczatkowy  U(x,0)= (1 dla x<0) (1 dla x>=0)
        if (fabs(h_levels[i]) < 1.0) U[0][i] = 1.0;
        else U[0][i] = 0.;


    for (int k = 1; k < N; k++) {
        //cout << k << endl;
        for (int i = 0; i < M; i++)
            x[i] = 0.0001;

        WSP[1][0] = 0.0; //l
        WSP[0][0] = 1.0; //d
        WSP[0][1] = 0.0; //u
        b[0] = U[k - 1][0];

        for (int i = 1; i < M - 1; i++) {

            WSP[i][i - 1] = lambda; //l
            WSP[i][i] = -(1 + 2 * lambda); //d
            WSP[i][i + 1] = lambda; //u
            b[i] = -U[k - 1][i];
        }

        WSP[M - 1][M - 2] = 0.0; //l
        WSP[M - 1][M - 1] = 1.0; //d
        WSP[M - 2][M - 1] = lambda; //u
        b[M - 1] = U[k - 1][M - 1];

        gauss_seidel(WSP, b, x);
        for (int i = 1; i < M - 1; i++)
            U[k][i] = x[i];
    }
    zapisz_plik(const_cast<char *>("wyniki_Lassonen_gaussseidel.txt"), U, N, M, h_levels);
}

void LU(double **A, double B[], double X[]) {
    double **L = nowa_macierz(M, M);
    double **U = nowa_macierz(M, M);
    double *y = new_vector(M);

    for (int i = 0; i < M; i++)
        for (int j = 0; j < M; j++) {
            L[i][j] = 0;
            U[i][j] = 0;
        }
    for (int i = 0; i < M; i++)
        L[i][i] = 1;

    //rozdzielam A na L i U
    for (int i = 0; i < M; i++) {
        double temp = 0;
        for (int j = 0; j < M; j++) {
            temp = 0;
            for (int k = 0; k < i; k++) {
                temp += L[i][k] * U[k][j];
            }
            U[i][j] = A[i][j] - temp;
        }

        for (int j = i + 1; j < M; j++) {
            temp = 0;
            for (int k = 0; k < i; k++) {
                temp += L[j][k] * U[k][i];
            }
            L[j][i] = (A[j][i] - temp) / U[i][i];
        }
    }

    for (int i = 0; i < M; i++) {
        y[i] = B[i];
        for (int j = 0; j < M; j++) {
            if (i > j)
                y[i] -= y[j] * L[i][j];
        }
    }

    //obliczam x z Ux = y
    for (int i = M - 1; i >= 0; i--) {
        X[i] = y[i];
        for (int j = M - 1; j >= 0; j--) {
            if (i < j)
                X[i] -= X[j] * U[i][j];
            else if (i == j)
                X[i] /= U[i][j];
        }
    }

}

void Lassonen_LU(double **U, int n, int m, double *dt_levels, double *h_levels) {
    double *x = new double[M];
    double *b = new double[M];
    double **WSP = new double *[M];
    for (int i = 0; i < M; i++)
        WSP[i] = new double[M];

    for (int i = 0; i < M; i++)
        for (int j = 0; j < M; j++)
            WSP[i][j] = 0;


    for (int i = 0; i < N; i++)    //warunek brzegowy Xm
        U[i][0] = 0.;
    for (int i = 0; i < N; i++)    //warunek brzegowy X0
        U[i][M - 1] = 0.;
    for (int i = 0; i < M; i++)  //warunek poczatkowy  U(x,0)= (1 dla x<0) (1 dla x>=0)
        if (fabs(h_levels[i]) < 1.0) U[0][i] = 1.0;
        else U[0][i] = 0.;


    for (int k = 1; k < N; k++) {
        //cout << k << endl;
        for (int i = 0; i < M; i++)
            x[i] = 0.0001;

        WSP[1][0] = 0.0; //l
        WSP[0][0] = 1.0; //d
        WSP[0][1] = 0.0; //u
        b[0] = U[k - 1][0];

        for (int i = 1; i < M - 1; i++) {

            WSP[i][i - 1] = lambda; //l
            WSP[i][i] = -(1 + 2 * lambda); //d
            WSP[i][i + 1] = lambda; //u
            b[i] = -U[k - 1][i];
        }

        WSP[M - 1][M - 2] = 0.0; //l
        WSP[M - 1][M - 1] = 1.0; //d
        WSP[M - 2][M - 1] = lambda; //u
        b[M - 1] = U[k - 1][M - 1];

        LU(WSP, b, x);
        for (int i = 1; i < M - 1; i++)
            U[k][i] = x[i];
    }
    zapisz_plik(const_cast<char *>("wyniki_Lassonen_LU.txt"), U, N, M, h_levels);
}

void wykres_bledu_od_kroku() {
    int zakres[6] = {10, 25, 50, 75, 100, 125};

    for (int i = 0; i < 6; i++) {

        ustaw_zmienne(zakres[i]);
        double *dt_levels1 = new double[N];
        double *h_levels1 = new double[M];
        fill_dt(dt_levels1, dt, N);
        fill_h(h_levels1, h, M);
        double **ANAL = nowa_macierz(N, M);
        analityczne(ANAL, N, M, dt_levels1, h_levels1);
        double **U = nowa_macierz(N, M);
        Lassonen_LU(U, N, M, dt_levels1, h_levels1);

        blad_od_h(ANAL, U, N, M, h_levels1, dt_levels1);

        delete[] dt_levels1;
        delete[] h_levels1;
        for (int j = N - 1; j > 0; j--)
            delete[]ANAL[j];
        delete[] ANAL;
        for (int j = N - 1; j > 0; j--)
            delete[]U[j];
        delete[] U;

    }
}

void zwykly(){
    double *dt_levels = new double[N]; // wektor poziomow czasowych
    double *h_levels = new double[M]; // wektor poziomow przestrzennych
    fill_dt(dt_levels, dt, N);
    fill_h(h_levels, h, M);


    ///////////////////////////////////////////////

    char *filename = const_cast<char *>("dt_przedzialy.txt"); // zapis poziomow czasowych do pliku, od 0 do 2
    char *filename2 = const_cast<char *>("h_przedzialy.txt"); // zapis poziomow przestrzennych do pliku, od -9.5 do 9.5
    ofstream file(filename);
    ofstream file2(filename2);
    file.setf(ios::fixed, ios::floatfield);
    file.precision(4);
    file2.setf(ios::fixed, ios::floatfield);
    file2.precision(4);
    for (int i = 0; i < M; i++)
        file2 << h_levels[i] << "\t" << i + 1 << endl;
    for (int i = 0; i < N; i++)
        file << dt_levels[i] << "\t" << i + 1 << endl;
    file.close();
    file2.close();
    cout << "Zapisano: " << filename << endl;
    cout << "Zapisano: " << filename2 << endl;

    double **ANAL = nowa_macierz(N, M);
    analityczne(ANAL, N, M, dt_levels, h_levels);

    double **U = nowa_macierz(N, M);
    Lassonen_LU(U, N, M, dt_levels, h_levels);

    double **U1 = nowa_macierz(N, M);
    Lassonen_GaussSeidel(U1, N, M, dt_levels, h_levels);

    double **BLAD = nowa_macierz(N, M);
    blad_LU(BLAD, ANAL, U, N, M, h_levels, dt_levels);

    double **BLAD2 = nowa_macierz(N, M);
    blad_gaussseidel(BLAD2, ANAL, U1, N, M, h_levels, dt_levels);


    for (int i = N - 1; i > 0; i--)
        delete[]ANAL[i];
    delete[] ANAL;

    for (int i = N - 1; i > 0; i--)
        delete[]U[i];
    delete[] U;

    for (int i = N - 1; i > 0; i--)
        delete[]U1[i];
    delete[] U1;

    for (int i = N - 1; i > 0; i--)
        delete[]BLAD[i];
    delete[] BLAD;

    for (int i = N - 1; i > 0; i--)
        delete[]BLAD2[i];
    delete[] BLAD2;

    delete[] dt_levels;
    delete[] h_levels;
}
int main() {

    //wykres_bledu_od_kroku();
    zwykly();

    return 0;
}



