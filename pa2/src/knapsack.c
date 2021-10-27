#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int max(int one, int two)
{
    if (one >= two) return one;
    else return two;
}

void printKnapsack(char** itemNames, int* itemWeights, int** matrix, int rows, int cols)
{
    if (rows <= 0 || cols < 0) return;

    int maxVal = matrix[rows][cols];
    while(matrix[rows][cols] == maxVal && cols > 0)
    {
        cols = cols-1;
    }
    if (matrix[rows][cols] != maxVal) cols = cols+1;

    printKnapsack(itemNames, itemWeights, matrix, rows-itemWeights[cols], cols-1);
    printf("%s\n", itemNames[cols]);
    return;
}

// void printMatrix(int** matrix, int rows, int cols)
// {
//     for (int i = 0; i < rows; i++)
//     {
//         for (int j = 0; j < cols; j++)
//         {
//             /*If entry is not the last entry in the row, print with a space*/
//             if (j < cols - 1) printf("%5d ", matrix[i][j]);
//             else printf("%5d", matrix[i][j]);
//         }
//         printf("\n");
//     }
// }

int main(int argc, char** argv)
{
    if (argc != 3) return EXIT_FAILURE;
    int weightLim = atoi(argv[1]);
    // printf("weightLim = %d\n", weightLim);
    FILE* file = fopen(argv[2], "r");    
    if (file == NULL) return EXIT_FAILURE;

    int numItems;
    fscanf(file, " %d", &numItems);
    // printf("numItems = %d\n", numItems);

    char** itemNames = malloc(numItems * sizeof(char*));
    for (int i = 0; i < numItems; i++)
    {
        itemNames[i] = malloc(31 * sizeof(char));
    }

    int* itemWeights = malloc(numItems * sizeof(int));
    int* itemValues = malloc(numItems * sizeof(int));
    for(int i = 0; i < numItems; i++)
    {
        fscanf(file, " %s", itemNames[i]);
        fscanf(file, " %d", &itemWeights[i]);
        fscanf(file, " %d", &itemValues[i]);
    }

    // for (int i = 0; i < numItems; i++)
    // {
    //     printf("%s ", itemNames[i]);
    //     printf("%d ", itemWeights[i]);
    //     printf("%d\n", itemValues[i]);
    // }

    int** matrix = malloc((weightLim+1) * sizeof(int*));
    for(int i = 0; i < weightLim+1; i++)
    {
        matrix[i] = malloc(numItems * sizeof(int));
    }
    for(int j = 0; j < numItems; j++)
    {
        matrix[0][j] = 0;
    }
    
    for (int i = 1; i < weightLim + 1; i++)
    {
        for (int j = 0; j < numItems; j++)
        {
            if (j == 0)
            {
                if (itemWeights[j] <= i) matrix[i][j] = itemValues[j];
                else matrix[i][j] = 0;
            }
            else if (i >= itemWeights[j])
            {
                matrix[i][j] = max(matrix[i][j-1], itemValues[j] + matrix[i-itemWeights[j]][j-1]);
            }
            else
            {
                matrix[i][j] = matrix[i][j-1];
            }
        }
    }
    // printMatrix(matrix, weightLim+1, numItems); 

    int maxVal = matrix[weightLim][numItems-1];    
    // printf("%d\n", maxVal);

    int maxRow = weightLim;
    int maxCol = numItems-1;

    while(matrix[maxRow][maxCol] == maxVal && maxRow > 0)
    {
        maxRow = maxRow-1;
    }

    if (matrix[maxRow][maxCol] != maxVal) maxRow = maxRow+1;

    while(matrix[maxRow][maxCol] == maxVal && maxCol > 0)
    {
        maxCol = maxCol-1;
    }

    if (matrix[maxRow][maxCol] != maxVal) maxCol = maxCol+1;

    printKnapsack(itemNames, itemWeights, matrix, maxRow, maxCol);

    printf("%d / %d\n", maxVal, maxRow);   

    for (int i = 0; i < weightLim+1; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
    free(itemValues);
    free(itemWeights);
    for (int i = 0; i < numItems; i++)
    {
        free(itemNames[i]);
    }
    free(itemNames);
    fclose(file);
    return EXIT_SUCCESS;
}