#include<stdio.h>

int main(void){
    int Unum, result;

    do {
        printf("input number: ");
        result = scanf("%d",&Unum);
        while(getchar() != '\n');
    }while(result != 1);

    printf("入力された数値: %d\n",Unum);
    return 0;
}