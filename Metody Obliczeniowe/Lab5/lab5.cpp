#include <iostream>
using namespace std;

int main(int argc, char** argv) {
	double A[4][4] = {{1, 20, -30, -4},
					 {4, 20, -6, 50}, 
					 {9, -18, 12, -11},
					 {16, -15, 14, 130}};
						  
	double b[4] = {0, 114, -5, 177};
	double y[4] = {0,0,0,0};
	double x[4] = {0,0,0,0};
	double L[4][4];
	double U[4][4];
	
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++){
			L[i][j] = 0;
			U[i][j] = 0;
		}	 
	for (int i = 0; i < 4; i++) 
		L[i][i] = 1;
	
	//rozdzielam A na L i U
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++)
		{
			double temp = 0;
			for (int k = 0; k < i; k++)
			{
				temp += L[i][k] * U[k][j];
			}
			U[i][j] = A[i][j] - temp;
		}

		for (int j = i + 1; j < 4; j++)
		{
			temp = 0;
			for (int k = 0; k < i; k++)
			{
				temp += L[j][k] * U[k][i];
			}
			L[j][i] = (A[j][i] - temp) / U[i][i];
		}		  
	}
	
	//obliczam y z Ly = b
	for(int i = 0; i < 4; i++){
		y[i] = b[i];		
		for(int j = 0; j < 4; j++){
			if(i > j)
				y[i] -= y[j] * L[i][j];		   
		}				 
	}
	
	//obliczam x z Ux = y
	for(int i = 3; i >= 0; i--){
		x[i] = y[i];		
		for(int j = 3; j >= 0; j--){
			if(i < j)
				x[i] -= x[j] * U[i][j];	
			else if (i == j)
				x[i] /= U[i][j]; 
		}				 
	}
	
	for(int i = 0; i < 4; i++){
		cout << y[i] << ' ';
	}
	
	
	cout << x[0] << endl << x[1] << endl << x[2] << endl << x[3] << endl ; 
	
	
	return 0;
}
