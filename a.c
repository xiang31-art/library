#include<stdio.h>
int main(void){
    int a[10] = {1,2,3,4,5,6,7,8,9,10}, *p;
    p = a;

    for(int i = 0; i < 10; i++){
        printf("%dtime\n",i + 1);
        printf("*p = %d\n",*p);
        printf("*p++=%d\n",*p++);
        printf("*p = %d\n",*p);
        printf("\n");
    }
    return 0;
}