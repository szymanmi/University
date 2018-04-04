#include <iostream>

int main(int argc, char** argv) {
	
	//// FLOAT ////
	float eps = 1.0;	
	float value = 2.0;
	int i = 0;				//licznik bitów mantysy
	while (value > 1.0) {	//pêtla dzia³a dopóki wartoœæ 1 + eps bêdzie > 1
		eps *= 0.5;			
		value = 1 + eps;
		if (value > 1.0)	//je¿eli wartoœæ przekroczy 1 to 
			i++;			//licznik bitów mantysy zwiêksza siê o 1
	}
	
	std::cout << "FLOAT  - EPS = " << eps*2 << "   i = " << i << std::endl;
	
	////DOUBLE////
	double eps1 = 1.0;
	double value1 = 2.0;
	i = 0;
	while (value1 > 1.0) {
		eps1 *= 0.5;
		value1 = 1 + eps1;
		if (value1 > 1.0)
			i++;
	}
	
	std::cout << "DOUBLE - EPS = " << eps1*2 << "   i = " << i << std::endl;  
	
	return 0;
}

