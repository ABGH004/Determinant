#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>
const int MAXN = 105;
double a[MAXN][MAXN];
// Gauss-Jordan Elimination O(n^3)
double determinant_first_approach(int n)
{
	double det = 1.0;
	for (int i = 0; i < n; i++) {
		int pivot = i;
		for (int j = i + 1; j < n; j++) {
			if (abs(a[j][i]) > abs(a[pivot][i])) {
				pivot = j;
			}
		}
		if (pivot != i) {
			std::swap(a[i], a[pivot]);
			det *= -1;
		}
		if (a[i][i] == 0) {
			return 0;
		}
		det *= a[i][i];
		for (int j = i + 1; j < n; j++) {
			double factor = a[j][i] / a[i][i];
			for (int k = i + 1; k < n; k++) {
				a[j][k] -= factor * a[i][k];
			}
		}
	}
	return det;
}

// Laplace Expansion O(n!)
double determinant_second_approach(double ** matrix, int size)
{
    int det = 0;
    int sign = 1;
 
    // Base Case
    if (size == 1) {
        det = matrix[0][0];
    }
    else if (size == 2) {
        det = (matrix[0][0] * matrix[1][1])
              - (matrix[0][1] * matrix[1][0]);
    }
 
    // Perform the Laplace Expansion
    else {
        for (int i = 0; i < size; i++) {
 
            // Stores the cofactor matrix
            double** cofactor = new double*[size - 1];
            for (int j = 0; j < size - 1; j++) {
                cofactor[j] = new double[size - 1];
            }
            int sub_i = 0, sub_j = 0;
            for (int j = 1; j < size; j++) {
                for (int k = 0; k < size; k++) {
                    if (k == i) {
                        continue;
                    }
                    cofactor[sub_i][sub_j] = matrix[j][k];
                    sub_j++;
                }
                sub_i++;
                sub_j = 0;
            }
 
            // Update the determinant value
            det += sign * matrix[0][i]
                   * determinant_second_approach(cofactor, size - 1);
            sign = -sign;
            for (int j = 0; j < size - 1; j++) {
                delete[] cofactor[j];
            }
            delete[] cofactor;
        }
    }
 
    // Return the final determinant value
    return det;
}
//rezaeifar
void determinant_third_approach();



int main()
{
	std::ifstream file("matrix.txt");
	std::string row;
	int length = -1;
	while(file){
		std::getline(file, row);
		++length;
	}
	file.close();
	file.open("matrix.txt");
	double** matrix = new double*[length];
	for( int i = 0; i < length; ++i )
		matrix[i] = new double[length];
	int i=0, j=0;
	while(file && i < length){
		
		std::getline(file, row);
	
		std::stringstream ss(row);
		std::string element;
		
		while(ss >> element && j < length){
			
			matrix[i][j] = stof(element);
			++j;
		}
		j = 0;
		++i;
		
	}
	
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++) {
			a[i][j] = matrix[i][j];
		}
	}
	double det1 = determinant_first_approach(length);
	double det2 = determinant_second_approach(matrix, length);
	std::cout << std::fixed << std::setprecision(2);
	std::cout << "Determinant = " << det1 << " " << det2 << std::endl;
	return 0;
}
