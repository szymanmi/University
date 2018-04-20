#include <iostream>
#include <iomanip>
#include <conio.h>
using namespace std;

void print_vector(double X[]) {
	cout.setf(ios::scientific);
	for(int i = 0; i < 4; i++)
		cout << setprecision(8) << X[i] << '\t';
	cout << endl;
}

void print_matrix(double **A){
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			cout <<setprecision(15)<< A[i][j] << '\t';
		}
		cout << endl;
	}
	cout << endl;
}

double **new_matrix(int n) {
	double **matrix = new double *[n];
	for(int i = 0; i < n; i++)
		matrix[i] = new double[n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			matrix[i][j] = 0;
	return matrix;
}

double **sum_2_matrices(double **A, double **B){
	double **result = new_matrix(4);
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			result[i][j] = A[i][j] + B[i][j];
	return result;
}

double **mul_2_matrices(double **A, double **B, int n) {
	double **solution = new_matrix(4);
	
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++){
			solution[i][j] = 0;
			for(int k = 0; k < n; k++)
				solution[i][j] += A[i][k] * B[k][j];
		}
		
	return solution;
}

double *new_vector(int n) {
	double *vector = new double[n];
	for(int i = 0; i < n; i++)
		vector[i] = 0;
	return vector;
}

double **mul_matrix_scalar(double **A, double s){
	double **result = new_matrix(4);
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			result[i][j] = A[i][j] * s;
	return result;
}

double *mul_matrix_vector(double **A, double *B, int n) {
	double *solution = new_vector(n);
	
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			solution[i] += B[j] * A[i][j];
		
	return solution;
}

void jacobi_method(double A[][4], double B[], double X[]) {
	double **D = new_matrix(4);
	double **LU = new_matrix(4);
	double *temp;
	
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if(i != j)
				LU[i][j] = A[i][j];
	
	for (int i = 0; i < 4; i++)
		D[i][i] = 1/A[i][i];		  

	double **M = mul_2_matrices(D, LU, 4);
	double *C = mul_matrix_vector(D, B, 4);
		
	for (int iter = 0; iter < 10; iter++) {		
		
		temp = mul_matrix_vector(M, X, 4);	

		for(int i = 0; i < 4; i++) 
			X[i] = C[i] - temp[i];
		print_vector(X);
		
	}	
}

double **gauss_jordan(double **A){
	double **D = new_matrix(4);
	double **T = new_matrix(4);
	for(int i = 0; i < 4; i++){
		T[i][i] = 1;
		for(int j = 0; j < 4; j++)
			D[i][j] = A[i][j];
	}		
	
	for(int i = 0; i < 4; i++){		
		double temp = D[i][i];
		for(int j = 0; j < 4; j++){	
			D[i][j] *= 1/temp;
			T[i][j] *= 1/temp;		
		}

		
		for(int j = 0; j < 4; j++){
			if(i != j){
				double temp2 = D[j][i] / D[i][i];
				for(int k = 0; k < 4; k++){
					D[j][k] -= D[i][k] * temp2;
					T[j][k] -= temp2 * T[i][k];
				}
			}
		}
			
		
	}

	return T;
}

void gauss_seidel(double A[][4], double B[], double X[]) {
	double **LD = new_matrix(4);
	double **U = new_matrix(4);
	
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++) {
			if(i >= j)
				LD[i][j] = A[i][j];
			else
				U[i][j] = A[i][j];
		}
		
	LD = gauss_jordan(LD);
	
	double **M = mul_2_matrices(LD, U, 4);
	double *C = mul_matrix_vector(LD, B, 4);
	
	
	for(int iter = 0; iter < 9; iter++){
		double *temp = mul_matrix_vector(M, X, 4);
		for(int i = 0; i < 4; i++)
			X[i] = C[i] - temp[i];
		print_vector(X);
	}
	
}

void sor(double A[][4], double B[], double X[], double omega){
	double **L = new_matrix(4);
	double **D = new_matrix(4);
	double **U = new_matrix(4);
	
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++){
			if(i < j)
				U[i][j] = A[i][j];
			else if (j < i)
				L[i][j] = A[i][j];
			else
				D[i][j] = A[i][j];
		}
	

	double *C = mul_matrix_vector(gauss_jordan(sum_2_matrices(L, mul_matrix_scalar(D, 1/omega))), B, 4);	
	
	double **M1 = gauss_jordan(sum_2_matrices(L, mul_matrix_scalar(D, 1/omega)));
	double **M2 = sum_2_matrices(U, mul_matrix_scalar(D, 1-1/omega));	
	double **M = mul_2_matrices(M1, M2, 4);
	
	
	for(int iter = 0; iter < 30; iter++){		
		double *temp = mul_matrix_vector(M, X, 4);
		for(int i = 0; i < 4; i++)
			X[i] = C[i] - temp[i];
		print_vector(X);
	}

}

int main(int argc, char** argv) {
	double A[4][4] = {{100, 1, -2, 3},
					{4, 300, -5, 6},
					{7, -8, 400, 9},
					{-10, 11, -12, 200}};
	double B[4] = {395, 603, -415, -606};
	double X[4] = {45, 15, -85, -54};
	double X1[4] = {45, 15, -85, -54};
	double X2[4] = {45, 15, -85, -54};
	double omega = 0.5;
	
	
	double **A2 = new_matrix(4);
	for(int i = 0; i< 4; i++)
		for(int j = 0; j < 4; j++)
			A2[i][j] = A[i][j];
		
	cout << "Jacobi\n";	
	jacobi_method(A, B, X);
	print_vector(X);
	cout << "\nGauss seidel\n";
	gauss_seidel(A, B, X1);
	print_vector(X1);
	cout << "\nsor\n";
	sor(A, B, X2, omega);
	print_vector(X2);
	
	return 0;
}

