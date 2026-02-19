#include <stdio.h>

int main() {
    printf("=== ネストループ課題の解答例 ===\n\n");
    
    // 課題1の解答: 5x5の正方形
    printf("課題1解答: 5x5の正方形\n");
    for (int i = 0; i < 5; i++) {        // 5行
        for (int j = 0; j < 5; j++) {    // 各行に5個の星
            printf("*");
        }
        printf("\n");  // 行の終わりで改行
    }
    printf("\n");
    
    // 課題2の解答: 直角三角形
    printf("課題2解答: 直角三角形\n");
    for (int i = 1; i <= 5; i++) {       // 5行
        for (int j = 1; j <= i; j++) {   // i行目にはi個の星
            printf("*");
        }
        printf("\n");
    }
    printf("\n");
    
    // 課題3の解答: 2次元配列の合計
    printf("課題3解答: 2次元配列の合計\n");
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    int sum = 0;
    for (int i = 0; i < 3; i++) {        // 3行
        for (int j = 0; j < 4; j++) {    // 4列
            sum += matrix[i][j];
            printf("matrix[%d][%d]=%d, 累計=%d\n", i, j, matrix[i][j], sum);
        }
    }
    printf("最終合計: %d\n\n", sum);
    
    // 課題4の解答: 九九の表（偶数のみ）
    printf("課題4解答: 九九の表（偶数のみ）\n");
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            int result = i * j;
            if (result % 2 == 0) {        // 偶数の場合のみ表示
                printf("%d×%d=%d ", i, j, result);
            }
        }
        printf("\n");
    }
    
    return 0;
}