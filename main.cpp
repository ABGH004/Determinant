#include <iostream>
#include <cmath>
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
	int n = 4;
	double** matrix = new double*[4];
	for( int i = 0; i < 4; ++i)
		matrix[i] = new double[4];

    matrix[0][0] = 1; matrix[0][1] = 0; matrix[0][2] = 2; matrix[0][3] = -1;
    matrix[1][0] = 3; matrix[1][1] = 0; matrix[1][2] = 0; matrix[1][3] = 5;
    matrix[2][0] = 2; matrix[2][1] = 1; matrix[2][2] = 4; matrix[2][3] = -3;
    matrix[3][0] = 1; matrix[3][1] = 0; matrix[3][2] = 5; matrix[3][3] = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			a[i][j] = matrix[i][j];
		}
	}
	double det1 = determinant_first_approach(n);
	double det2 = determinant_second_approach(matrix, n);
	std::cout << "Determinant = " << det1 << " " << det2 << std::endl;

	return 0;
}
