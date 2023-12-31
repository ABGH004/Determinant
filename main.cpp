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
			if ( abs(a[j][i]) > abs(a[pivot][i]) ) {
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
// Rezaeifar O(2^n)
double determinant_third_approach(double** matrix, int size)
{
	if(size == 1)
		return matrix[0][0];
	if(size == 2 )
		return (matrix[0][0] * matrix[1][1])
              - (matrix[0][1] * matrix[1][0]);
	
	double** mat1 = new double*[size-1];
	for( int i = 0; i < size-1; ++i )
		mat1[i] = new double[size-1];
	
	double** mat2 = new double*[size-1];
	for( int i = 0; i < size-1; ++i )
		mat2[i] = new double[size-1];
	
	double** mat3 = new double*[size-1];
	for( int i = 0; i < size-1; ++i )
		mat3[i] = new double[size-1];
	
	double** mat4 = new double*[size-1];
	for( int i = 0; i < size-1; ++i )
		mat4[i] = new double[size-1];
	
	double** denominator = new double*[size-2];
	for( int i = 0; i < size-2; ++i )
		denominator[i] = new double[size-2];
	
	double numinator[2][2];
	
	for(int i = 1; i < size; ++i)
		for(int j = 1; j < size; ++j)
			mat1[i-1][j-1] = matrix[i][j];
	
	for(int i = 1; i < size; ++i)
		for(int j = 0; j < size-1; ++j)
			mat2[i-1][j] = matrix[i][j];

	for(int i = 0; i < size-1; ++i)
		for(int j = 1; j < size; ++j)
			mat3[i][j-1] = matrix[i][j];
	
	for(int i = 0; i < size-1; ++i)
		for(int j = 0; j < size-1; ++j)
			mat4[i][j] = matrix[i][j];
	
	numinator[0][0] = determinant_third_approach(mat1, size-1);
	numinator[0][1] = determinant_third_approach(mat2, size-1);
	numinator[1][0] = determinant_third_approach(mat3, size-1);
	numinator[1][1] = determinant_third_approach(mat4, size-1);
	
	for(int i = 1; i < size-1; ++i)
		for(int j = 1; j < size-1; ++j)
			denominator[i-1][j-1] = matrix[i][j];
	
	double det = determinant_third_approach(denominator, size-2);
	
	if(det == 0)
		throw("UNDEFINED: ZERO DIVISION TRY OTHER APPROACHES);
	
	return ((numinator[0][0] * numinator[1][1])
			- (numinator[0][1] * numinator[1][0]))/ det;
}


void reader(double **&matrix, std::string fileName, int &length)
{
	std::ifstream file(fileName);
	std::string row;
	
	while(file){
		std::getline(file, row);
		++length;
	}
	
	file.close();
	file.open(fileName);
	
	matrix = new double*[length];
	
	for( int i = 0; i < length; ++i )
		matrix[i] = new double[length];
	
	int i=0, j=0;
	
	while( file && i < length ){
		
		std::getline(file, row);
	
		std::stringstream ss(row);
		std::string element;
		
		while( ss >> element ){
			
			matrix[i][j] = stof(element);
			++j;
		}
		if( j != length )
			throw("UNDEFINED: MATRIX IS NOT SQUARE");
		j = 0;
		++i;
		
	}
}
int main()
{
	std::string fileName;
	std::getline(std::cin, fileName);
	int length = -1;
	double** matrix;
	fileName = "samples/" + fileName;
	try
	{
		reader(matrix, fileName, length);
	}
	catch(const char * error)
	{
		std::cerr << error << std::endl;
		return -1;
	}
	
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++) {
			a[i][j] = matrix[i][j];
		}
	}
	
	double det1 = determinant_first_approach(length);
	double det2 = determinant_second_approach(matrix, length);
	
	std::cout << std::fixed << std::setprecision(2);
	std::cout << "Determinant(Gauss) = " << det1 << std::endl;
	std::cout << "Determinant(Laplace) = " << det2 << std::endl;
	
	try{
		double det3 = determinant_third_approach(matrix, length);
		std::cout << "Determinant(Rezaeifar) = " << det3 << std::endl;
	}
	catch(const char* error)
	{
		std::cerr << error << std::endl;
	}
	for(int i = 0; i < length; ++i)
		delete [] matrix[i];
	delete [] matrix;

	return 0;
}
