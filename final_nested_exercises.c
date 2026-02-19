#include <stdio.h>

int main() {
    printf("=== ネストループ実践課題（最終版） ===\n\n");
    
    // 課題1: 星印で正方形を描く
    printf("課題1: 星印で5x5の正方形\n");
    printf("期待する出力:\n");
    printf("*****\n*****\n*****\n*****\n*****\n\n");
    printf("あなたのコード結果:\n");
    
    for(int a = 1; a <= 5; a++) {
        for(int b = 1; b <= 5; b++) {
            printf("*");
        }
        printf("\n");
    }
    
    printf("\n");
    
    // 課題2: 直角三角形を描く
    printf("課題2: 星印で直角三角形\n");
    printf("期待する出力:\n");
    printf("*\n**\n***\n****\n*****\n\n");
    printf("あなたのコード結果:\n");
    
    for(int a = 1; a <= 5; a++) {
        for(int b = 1; b <= a; b++) {
            printf("*");
        }
        printf("\n");
    }
    
    printf("\n");
    
    // 課題3: 2次元配列の合計を求める
    printf("課題3: 2次元配列の全要素の合計\n");
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    printf("配列の内容:\n");
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
    
    printf("合計: %d\n\n", sum);
    
    // 課題4: 九九の表（条件付き）- 改良版
    printf("課題4: 九九の表で、結果が偶数のもののみ表示\n");
    
    for(int a = 1; a <= 9; a++) {
        printf("%d段: ", a);
        for(int b = 1; b <= 9; b++) {
            if(a * b % 2 == 0) {
                printf("%dx%d=%d ", a, b, a*b);
            }
        }
        printf("\n");
    }
    
    printf("\n=== 全課題完了！ ===\n");
    return 0;
}