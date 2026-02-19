#include <stdio.h>

int main() {
    printf("=== 上級者向けネストループテクニック ===\n\n");
    
    // 1. 三角形の範囲でのループ（i <= j の条件）
    printf("1. 三角形範囲のループ\n");
    for (int i = 0; i < 4; i++) {
        for (int j = i; j < 4; j++) {  // j は i から開始
            printf("(%d,%d) ", i, j);
        }
        printf("\n");
    }
    printf("\n");
    
    // 2. 対称行列の処理（重複を避ける）
    printf("2. 対称行列の効率的な処理\n");
    int matrix[4][4];
    
    // 上三角部分のみ処理（効率的）
    for (int i = 0; i < 4; i++) {
        for (int j = i; j < 4; j++) {
            matrix[i][j] = i + j;
            matrix[j][i] = i + j;  // 対称位置にも同じ値を設定
            printf("matrix[%d][%d] = %d\n", i, j, matrix[i][j]);
        }
    }
    printf("\n");
    
    // 3. break と continue の使い分け
    printf("3. break と continue の効果的な使用\n");
    for (int i = 1; i <= 5; i++) {
        printf("外側ループ i=%d: ", i);
        for (int j = 1; j <= 5; j++) {
            if (j == 3) {
                printf("[skip3] ");
                continue;  // j=3をスキップ
            }
            if (i * j > 10) {
                printf("[break] ");
                break;     // 内側ループを抜ける
            }
            printf("%d ", i * j);
        }
        printf("\n");
    }
    printf("\n");
    
    // 4. ラベル付きbreak（上級テクニック）
    printf("4. 多重ループからの脱出\n");
    outer_loop:  // ラベル
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            printf("(%d,%d) ", i, j);
            if (i == 2 && j == 2) {
                printf("[全ループ終了] ");
                goto end_loops;  // 全てのループから脱出
            }
        }
        printf("\n");
    }
    end_loops:
    printf("\n完了\n");
    
    return 0;
}