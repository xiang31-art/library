#include <stdio.h>

int main() {
    printf("=== Nested Loop Practice Exercises ===\n\n");
    
    // Exercise 1: Draw a square with stars
    printf("Exercise 1: Draw a 5x5 square with stars\n");
    printf("Expected output:\n");
    printf("*****\n*****\n*****\n*****\n*****\n\n");
    printf("Your code result:\n");
    
    for(int a = 1; a <= 5; a++) {
        for(int b = 1; b <= 5; b++) {
            printf("*");
        }
        printf("\n");
    }
    
    printf("\n");
    
    // Exercise 2: Draw a right triangle
    printf("Exercise 2: Draw a right triangle with stars\n");
    printf("Expected output:\n");
    printf("*\n**\n***\n****\n*****\n\n");
    printf("Your code result:\n");
    
    for(int a = 1; a <= 5; a++) {
        for(int b = 1; b <= a; b++) {
            printf("*");
        }
        printf("\n");
    }
    
    printf("\n");
    
    // Exercise 3: Sum of 2D array elements
    printf("Exercise 3: Sum all elements in 2D array\n");
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    printf("Array contents:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
    
    int sum = 0;
    for(int a = 0; a < 3; a++) {
        for(int b = 0; b < 4; b++) {
            sum += matrix[a][b];
        }
    }
    
    printf("Total sum: %d\n\n", sum);
    
    // Exercise 4: Multiplication table (even results only)
    printf("Exercise 4: Multiplication table (even results only)\n");
    
    for(int a = 1; a <= 9; a++) {
        printf("Row %d: ", a);
        for(int b = 1; b <= 9; b++) {
            if(a * b % 2 == 0) {
                printf("%dx%d=%d ", a, b, a*b);
            }
        }
        printf("\n");
    }
    
    printf("\n=== All exercises completed! ===\n");
    return 0;
}