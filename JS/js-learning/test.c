#include<stdio.h>

int main(void){
    for(int j = 1; j <= 9; j++){
        for(int i = 1; i <=9; i++){
            printf("%2d×%2d= %2d ", j, i, j * i);
        }
    printf("\n");
    }
    return 0;
}