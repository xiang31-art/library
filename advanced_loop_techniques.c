#include <stdio.h>

int main() {
    printf("=== Advanced Loop Techniques ===\n\n");
    
    // 1. 3重ループ（3次元配列）
    printf("1. Triple nested loop (3D array)\n");
    int cube[2][3][2] = {
        {{1, 2}, {3, 4}, {5, 6}},
        {{7, 8}, {9, 10}, {11, 12}}
    };
    
    printf("3D array contents:\n");
    for (int layer = 0; layer < 2; layer++) {
        printf("Layer %d:\n", layer);
        for (int row = 0; row < 3; row++) {
            printf("  Row %d: ", row);
            for (int col = 0; col < 2; col++) {
                printf("%2d ", cube[layer][row][col]);
            }
            printf("\n");
        }
        printf("\n");
    }
    
    // 2. break文の効果的な使用
    printf("2. Effective use of break statement\n");
    printf("Finding first number divisible by 7 in range 20-50:\n");
    for (int i = 20; i <= 50; i++) {
        if (i % 7 == 0) {
            printf("Found: %d\n", i);
            break;  // 最初の1つを見つけたら終了
        }
        printf("Checking: %d\n", i);
    }
    printf("\n");
    
    // 3. continue文の効果的な使用
    printf("3. Effective use of continue statement\n");
    printf("Even numbers from 1 to 10 (skipping odd numbers):\n");
    for (int i = 1; i <= 10; i++) {
        if (i % 2 != 0) {
            continue;  // 奇数をスキップ
        }
        printf("%d ", i);
    }
    printf("\n\n");
    
    // 4. ラベル付きbreak（多重ループからの脱出）
    printf("4. Labeled break (escaping from multiple loops)\n");
    printf("Finding pair (i,j) where i*j = 12:\n");
    
    outer_loop:
    for (int i = 1; i <= 6; i++) {
        for (int j = 1; j <= 6; j++) {
            printf("Checking: %d * %d = %d\n", i, j, i*j);
            if (i * j == 12) {
                printf("Found pair: (%d, %d)\n", i, j);
                goto exit_loops;  // 全てのループから脱出
            }
        }
    }
    exit_loops:
    printf("\n");
    
    // 5. ループの最適化テクニック
    printf("5. Loop optimization techniques\n");
    printf("Calculating sum of squares (optimized):\n");
    
    int sum = 0;
    int limit = 100;
    
    // 最適化: 条件を事前に計算
    for (int i = 1; i <= limit; i++) {
        int square = i * i;  // 計算結果を変数に保存
        sum += square;
        if (i <= 5) {  // 最初の5個だけ表示
            printf("%d^2 = %d, sum = %d\n", i, square, sum);
        }
    }
    printf("Final sum of squares (1 to %d): %d\n\n", limit, sum);
    
    return 0;
}