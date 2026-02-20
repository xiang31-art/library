#include <stdio.h>

int main() {
    printf("=== ループ文の基礎学習 ===\n\n");
    
    // 1. for文の基本形
    printf("1. for文 - 繰り返し回数が決まっている場合\n");
    printf("1から5まで表示:\n");
    for (int i = 1; i <= 5; i++) {
        printf("%d ", i);
    }
    printf("\n\n");
    
    // 2. while文の基本形
    printf("2. while文 - 条件が満たされる間繰り返す\n");
    printf("1から5まで表示:\n");
    int j = 1;
    while (j <= 5) {
        printf("%d ", j);
        j++;
    }
    printf("\n\n");
    
    // 3. do-while文の基本形
    printf("3. do-while文 - 最低1回は実行される\n");
    printf("1から5まで表示:\n");
    int k = 1;
    do {
        printf("%d ", k);
        k++;
    } while (k <= 5);
    printf("\n\n");
    
    return 0;
}