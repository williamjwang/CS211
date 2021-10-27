#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void multiplyMatrix(int** mainMatrix, int** matrix2, int dim)
{
    /*Make a copy of the main matrix*/
    int** matrixCopy = malloc(dim * sizeof(int*));
        for (int i = 0; i < dim; i++)
        {
            matrixCopy[i] = malloc(dim * sizeof(int));
        }
        for (int i = 0; i < dim; i++)
        {
            for (int j = 0; j < dim; j++)
            {
                matrixCopy[i][j] = mainMatrix[i][j];
            }
        }

    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            int value = 0;

            /*Allocate memory for the row and column vectors*/
            int* row = (int*)malloc(sizeof(int) * dim);
            int* col = (int*)malloc(sizeof(int) * dim);

            /*Initialize row and column vectors*/
            for(int k = 0; k < dim; k++)
            {
                row[k] = matrixCopy[i][k];
            }
            for (int k = 0; k < dim; k++)
            {
                col[k] = matrix2[k][j];
            }

            /*Find the dot product DP of the row and column vectors*/
            for (int k = 0 ; k < dim; k++)
            {
                value = value + (row[k] * col[k]);
            }

            /*Row and column vectors no longer needed for this iteration*/
            free(row);
            free(col);

            /*Set the value at mainMatrix[i][j] to be DP*/
            mainMatrix[i][j] = value;
        }
    }

    /*Free the memory allocated for matrixCopy*/
    for (int i = 0; i < dim; i++)
    {
        free(matrixCopy[i]);
    }
    free(matrixCopy);
}

void printMatrix(int** matrix, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            /*If entry is not the last entry in the row, print with a space*/
            if (j < size - 1) printf("%d ", matrix[i][j]);
            else printf("%d", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char** argv)
{
    if (argc != 2) return EXIT_FAILURE;

    FILE* file = fopen(argv[1], "r");
        
    if (file == NULL) return EXIT_FAILURE;
    
    /*Read dimensions n of square matrix*/
    int size;    
    fscanf(file, " %d", &size);

    int** matrix = malloc(size * sizeof(int*));
    for(int i = 0; i < size; i++)
    {
        matrix[i] = malloc(size * sizeof(int));
    }

    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            fscanf(file, " %d", &matrix[i][j]);
        }
    }

    int power;
    fscanf(file, " %d", &power);

    if (power == 0)
    {
        /*If power is 0, change matrix to identity matrix*/
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (i == j) matrix[i][j] = 1;
                else matrix[i][j] = 0;
            }
        }

        /*Then print the matrix*/
        printMatrix(matrix, size);
    }
    if (power == 1)
    {
        /*If power is 1, print the matrix*/
        printMatrix(matrix, size);
    }
    if (power >= 2)
    {
        /*Make copy of matrix to copy from */
        int** matrixCopy = malloc(size * sizeof(int*));
        for (int i = 0; i < size; i++)
        {
            matrixCopy[i] = malloc(size * sizeof(int));
        }
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                matrixCopy[i][j] = matrix[i][j];
            }
        }

        /*Multiply the matrix by the copy of original matrix power-1 times*/
        for (int i = 0; i < power-1; i++)
        {
            multiplyMatrix(matrix, matrixCopy, size);
        }

        /*Done multiplying matrix, matrixCopy no longer needed*/
        /*Free the memory allocated for matrixCopy*/
        for(int i = 0; i < size; i++)
        {
            free(matrixCopy[i]);
        }
        free(matrixCopy);

        /*Print the resulting matrix*/
        printMatrix(matrix, size);
    }    
    
    /*Free the matrix itself*/
    for (int i = 0; i < size; i++)
    {
        free(matrix[i]);
    }
    free(matrix);

    /*Close the input file*/
    fclose(file);
    return EXIT_SUCCESS;
}