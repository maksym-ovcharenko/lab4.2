#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** memory_allocation(int rows, int cols);
void clear_memory(int rows, int cols, int** matrix);
void initialize_matrix(int rows, int cols, int** matrix);
void display_matrix(int rows, int cols, int** matrix, char name);
void display_trans_matrix(int cols, int rows, int** matrix, char name);
void find_minimum(int rows, int cols, int** matrix);
void find_maximum(int rows, int cols, int** matrix);
void sum_elements(int rows, int cols, int** matrix);
void transpone_matrix(int cols, int rows, int** matrix_orig, int** transponed_matrix);
int** multiply_matrices(int rows_A, int rows_B, int cols_A, int cols_B, int** matrix_A, int** matrix_B);
int** sort_matrix (int rows, int cols, int**matrix);

int main()
{
	int rows_A = 3, cols_A = 3;
	int rows_B = 3, cols_B = 4;
	char name_A = 'A';
	char name_B = 'B';
	char name_C = 'C';
    char name_D = 'D';

	int** A = memory_allocation(rows_A, cols_A);
	int** B = memory_allocation(rows_B, cols_B);
	int** B_transponed = memory_allocation(rows_B, cols_B);

	initialize_matrix(rows_A, cols_A, A);
	initialize_matrix(rows_B, cols_B, B);
    transpone_matrix(rows_B, cols_B, B, B_transponed);

	int** C = multiply_matrices(rows_A, rows_B, cols_A, cols_B, A, B);

	display_matrix(rows_B, cols_B, B, name_B);
	display_matrix(rows_A, cols_A, A, name_A);
	display_matrix(rows_A, cols_B, C, name_C);

    sum_elements(rows_A, cols_A, A);

	display_trans_matrix(rows_B, cols_B, B_transponed, name_B);

	find_minimum(rows_A, cols_A, A);
	find_maximum(rows_A, cols_A, A);

    A = sort_matrix(rows_A, cols_A, A);
    display_matrix(rows_A, cols_A, A, name_D);

	clear_memory(rows_A, cols_A, A);
	clear_memory(rows_B, cols_B, B);
	clear_memory(cols_B, rows_A, B_transponed);
	clear_memory(rows_A, cols_B, C);
	printf("\n\n");
	return 0;

}


int** memory_allocation(int rows, int cols)
{
	int** matrix = (int**)malloc(rows * sizeof(int*));
	for (int m = 0; m < cols; m++)
	{
		matrix[m] = (int*)malloc(cols * sizeof(int));
	}
	if (matrix == NULL) {
		printf("Memory not allocated.\n");
		exit(0);
	}
	return matrix;
}
void clear_memory(int rows, int cols, int** matrix)
{
	for (int i = 0; i < rows; i++)
	{
		free(matrix[i]);
	}

	free(matrix);
}
void initialize_matrix(int rows, int cols, int** matrix)
{
    srand(time(0)); int num = 0, upper = 30, lower = 1;

	for (int m = 0; m < rows; m++)
	{

		for (int n = 0; n < cols; n++)
		{
		    num = (rand() % (upper - lower + 1)) + lower;
			matrix[m][n] = num;
		}
	}
}
void initialize_matrix_zero(int rows, int cols, int** matrix)
{
	int count = 0;

	for (int m = 0; m < rows; m++)
	{
		for (int n = 0; n < cols; n++)
		{
			matrix[m][n] = count;
		}
	}
}
void display_matrix(int rows, int cols, int** matrix, char name)
{

	printf("\n\tMATRIX %c", name);
	for (int m = 0; m < rows; m++)
	{
		printf("\n");
		for (int n = 0; n < cols; n++)
		{
			printf("\t\t[%u][%u] = %u", (m + 1), (n + 1), matrix[m][n]);

		}
	}
}
void display_trans_matrix(int cols, int rows, int** matrix, char name)
{

	printf("\n\tTRANSPONED MATRIX %c", name);
	for (int m = 0; m < rows; m++)
	{
		printf("\n");
		for (int n = 0; n < cols; n++)
		{
			printf("\t\t[%u][%u] = %u", (m + 1), (n + 1), matrix[m][n]);

		}
	}
	printf("\n");
}
void find_minimum(int rows, int cols, int** matrix)
{
	int row = 0, col = 0;
	int minimum = matrix[0][0];

	for (int m = 0; m < cols; m++)
	{
		for (int n = 0; n < cols; n++)
		{
			if (matrix[m][n] < minimum)
			{
				minimum = matrix[m][n];
				row = m;
				col = n;
			}

		}
	}
	printf("\n\tThe element[%u][%u] has the smallest value : %u", row + 1, col + 1, minimum);
}
void find_maximum(int rows, int cols, int** matrix)
{
	int row = 0, col = 0;
	int maximum = matrix[0][0];

	for (int m = 0; m < cols; m++)
	{
		for (int n = 0; n < cols; n++)
		{
			if (matrix[m][n] > maximum)
			{
				maximum = matrix[m][n];
				row = m;
				col = n;
			}

		}
	}
	printf("\n\n\tThe element[%u][%u] has the biggest value  : %u\n", row + 1, col + 1, maximum);
}
void transpone_matrix(int cols, int rows, int** matrix_orig, int** transponed_matrix)
{

	for (int m = 0; m < rows; m++)
	{
		for (int n = 0; n < cols; n++)
		{
			transponed_matrix[m][n] = matrix_orig[n][m];
		}
	}
	printf("\n");
}
int** multiply_matrices(int rows_A, int rows_B, int cols_A, int cols_B, int** matrix_A, int** matrix_B)
{
	int rows_C = rows_A;
	int cols_C = cols_B;
	int** matrix_C = memory_allocation(rows_C, cols_C);
    initialize_matrix_zero(rows_C, cols_C, matrix_C);
	int product = 0, n = 0, m = 0, j = 0;

	if (cols_A != rows_B)
	{
		printf("\n!Matrices cannot be multiplied!\n");
		exit(0);
	}
	for (m = 0; m < rows_C; m++) // зміна рядку
	{
		for (n = 0; n < cols_C; n++) // перебирання елементів у межах одного рядку - зсунення стовпців - заповнення одного рядку
		{
			for (j = 0; j < rows_C; j++) // знаходження одного певного елементу - знаходження суми добутку рядка на стовпець
			{
				product = 0;
				product = matrix_A[m][j] * matrix_B[j][n];
				matrix_C[m][n] += product;
			}
		}
	}
	return matrix_C;
}
int** sort_matrix (int rows, int cols, int** matrix)
{
     int temp;
     for (int m = 0; m < rows; m++)
     {
       for (int k = 0; k < (cols - 1); k++)
       {
         for (int n = 0; n < (cols - 1); n++)
         {
            if (matrix[m][n] > matrix[m][n + 1])
               {
                   temp = matrix[m][n + 1];
                   matrix[m][n + 1] = matrix[m][n];
                   matrix[m][n] = temp;
               }
         }
       }
     }
     return matrix;
}
void sum_elements(int rows, int cols, int** matrix)
{
    int sum = 0;
    for (int m = 0; m < rows; m++)
    {
        for (int n = 0; n < rows; n++ )
        {
            sum += matrix[m][n];
        }
    }
    printf ("\n\n\tSum of the elements equals : %d\n", sum);
}
