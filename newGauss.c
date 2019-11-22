/**
 * @name Gaussian Elimination
 * @author Toyoabasi Udosen
 * @version 1.0.0
 * @date Wed Nov 20 2019, 6:15:40am
*/ 
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#define NUMOFEQUATIONS 3 // No more than 3 equations
#define NUMOFTERMS 4 // 3 terms per equation
/**
 * @name funcArray
 * @brief  Struct. contains array in which matrix will be stored
 * @note   
 * @retval None
 */
typedef struct
{
    float arr[NUMOFEQUATIONS][NUMOFTERMS];
}funcArray;


/**
 * @name backSub
 * @brief  Performs back substituition and prints results of X1, X2 and X3
 * @note   
 * @param  arr[][NUMOFTERMS]: Holds values in the matrix
 * @param  noOfEquations: Number of equations in the system
 * @retval None
 */
void backSub(float arr[][NUMOFTERMS], int noOfEquations )
{
    float answers[noOfEquations];
    float answer;
    for (int row = noOfEquations - 1; row >= 0; row--)
    {
        answer = 0;
        for (int col = row + 1; col <= noOfEquations - 1; col++ )
        {
            answer = answer + arr[row][col] * answers[col];
        }
        answers[row] = (arr[row][noOfEquations] - answer) / arr[row][row];
    }
    
    printf("------------SOLUTION---------------------------\n");
    for (size_t i = 0; i < noOfEquations; i++)
    {
        printf("X%d: %.4f\n", i + 1, answers[i] );
    }
    printf("---------------------------------------\n");
    
    
}

/**
 * @name partPivot
 * @brief  Performs partial pivot. Swap rows to bring row with highest coefficient to the top
 * @note   
 * @param  arr[][NUMOFTERMS]: Holds values in the matrix
 * @param  noOfEquations: Number of equations in the system
 * @retval None
 */
void partPivot(float arr[][NUMOFTERMS], int noOfEquations )
{
    double swap;
    for (int i = 0; i < noOfEquations; i++)
    {
        for (int j = i + 1; j < noOfEquations; j++) 
        {
            if (abs(arr[i][i]) < abs(arr[j][i]))
            {
                for (int k = 0; k < noOfEquations + 1; k++)
                {
                    swap = arr[i][k];
                    arr[i][k] = arr[j][k];
                    arr[j][k] = swap;
                }
                
            }
        }
        
    }
    
}


/**
 * @name gaussElim
 * @brief  Put equatons in row echelon format
 * @note   
 * @param  arr[][NUMOFTERMS]: Holds values in the matrix
 * @param  noOfEquations: Number of equations in the system
 * @retval None
 */
void gaussElim(float arr[][NUMOFTERMS], int noOfEquations)
{
    float factor;
    for(int i = 0; i < noOfEquations - 1; i++)
    {
        for(int j = i + 1; j < noOfEquations; j++)
        {
            factor = arr[j][i] / arr[i][i];
            for(int k = 0; k < noOfEquations + 1; k++)
            {
              arr[j][k] = arr[j][k] - factor * arr[i][k];
            }
        }
    }
    
}


int main()
{
    funcArray func, funcRet;
    int noOfEquations;
    bool flag = true;

    for(;;) // Loop allows for validation until the right input is provided
    {
        printf("How many equations would you like to solve?\n");
        scanf("%d", &noOfEquations);
        if (noOfEquations <= NUMOFEQUATIONS)
        {
            break;
        }
        printf("Error! No more than 3 equations can be solved.\n");
    }
    

    printf("Fill the matrix (row by row ): \n");
    for (int i = 0; i < noOfEquations; i++)
    {
        for (int j = 0; j < NUMOFTERMS; j++)
        {
            scanf("%f", &func.arr[i][j]);
        }
    }


    printf("------------MATRIX---------------------------\n");
    for (int i = 0; i <  noOfEquations; i++)
    {   
        for (int j = 0; j < NUMOFTERMS; j++)
        {
            printf("%.4f", func.arr[i][j]);
            printf("     ");
        }
        printf("\n");
    }
    printf("---------------------------------------------\n");

    funcRet = func;

    printf("Performing Gaussian elimination...\n");
    sleep(3);
    gaussElim(funcRet.arr, noOfEquations); 

    printf("------------MATRIX (ROW-ECHELON)---------------------------\n");
    for (int i = 0; i <  noOfEquations; i++)
    {   
        for (int j = 0; j < NUMOFTERMS; j++)
        {
            printf("%.4f", funcRet.arr[i][j]);
            printf("     ");
        }
        printf("\n");
    }
    printf("---------------------------------------------\n");


    printf("Solution: \n");
    backSub(funcRet.arr, noOfEquations);

        
    printf("Performing partial pivot... \n");
    partPivot(func.arr, noOfEquations);
    sleep(3);

    printf("------------MATRIX (After Pivot)---------------------------\n");
    for (int i = 0; i <  noOfEquations; i++)
    {   
        for (int j = 0; j < NUMOFTERMS; j++)
        {
            printf("%.4f", func.arr[i][j]);
            printf("     ");
        }
        printf("\n");
    }
    printf("---------------------------------------------\n");
    

    printf("Performing Gaussian elimination...\n");
    sleep(3);
    gaussElim(func.arr, noOfEquations);

    printf("------------MATRIX (ROW-ECHELON)---------------------------\n");
    for (int i = 0; i <  noOfEquations; i++)
    {   
        for (int j = 0; j < NUMOFTERMS; j++)
        {
            printf("%.4f", func.arr[i][j]);
            printf("     ");
        }
        printf("\n");
    }
    printf("---------------------------------------------\n");

    printf("Solution (With partial pivot): \n");
    backSub(func.arr, noOfEquations);
}

