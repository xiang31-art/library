#include <stdio.h>

int main() {
    printf("=== ネストしたループの基礎 ===\n\n");
    
    // 1. 基本的なネストループ
    printf("1. 基本的なネストループ (3x3の格子)\n");
    for (int i = 0; i < 3; i++) {        // 外側のループ（行）
        for (int j = 0; j < 3; j++) {    // 内側のループ（列）
            printf("(%d,%d) ", i, j);
        }
        printf("\n");  // 行の終わりで改行
    }
    printf("\n");
    
    // 2. 実行順序の理解
    printf("2. 実行順序の可視化\n");
    int count = 1;
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            printf("実行順序%d: 外側i=%d, 内側j=%d\n", count++, i, j);
        }
    }
    printf("\n");
    
    // 3. 異なるサイズのネストループ
    printf("3. 異なるサイズのネストループ\n");
    for (int i = 1; i <= 4; i++) {       // 外側: 1から4
        for (int j = 1; j <= 2; j++) {   // 内側: 1から2
            printf("[%d-%d] ", i, j);
        }
        printf("\n");
    }
    
    return 0;
}