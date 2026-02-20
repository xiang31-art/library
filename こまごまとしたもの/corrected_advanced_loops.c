#include <stdio.h>

int main() {
    printf("=== Corrected Advanced Loop Techniques ===\n\n");
    
    // 1. 正しいgoto文の使用例
    printf("1. Correct use of goto statement\n");
    printf("Finding pair (i,j) where i*j = 12:\n");
    
    for (int i = 1; i <= 6; i++) {
        for (int j = 1; j <= 6; j++) {
            printf("Checking: %d * %d = %d\n", i, j, i*j);
            if (i * j == 12) {
                printf("Found pair: (%d, %d)\n", i, j);
                goto found_result;  // ラベル名を一致させる
            }
        }
    }
    found_result:  // goto文の飛び先
    printf("Search completed.\n\n");
    
    // 2. フラグ変数を使った方法（より推奨される）
    printf("2. Using flag variable (recommended approach)\n");
    printf("Finding pair (x,y) where x*y = 20:\n");
    
    int found = 0;  // フラグ変数
    for (int x = 1; x <= 10 && !found; x++) {  // !foundで条件追加
        for (int y = 1; y <= 10; y++) {
            printf("Checking: %d * %d = %d\n", x, y, x*y);
            if (x * y == 20) {
                printf("Found pair: (%d, %d)\n", x, y);
                found = 1;  // フラグを立てる
                break;      // 内側ループを抜ける
            }
        }
    }
    printf("Search completed.\n\n");
    
    // 3. 関数を使った方法（最も推奨される）
    printf("3. Using function (best practice)\n");
    printf("Finding pair (a,b) where a*b = 15:\n");
    
    // 関数内で処理することで、returnで全体から抜けられる
    for (int a = 1; a <= 10; a++) {
        for (int b = 1; b <= 10; b++) {
            printf("Checking: %d * %d = %d\n", a, b, a*b);
            if (a * b == 15) {
                printf("Found pair: (%d, %d)\n", a, b);
                return 0;  // main関数から抜ける（プログラム終了）
            }
        }
    }
    
    return 0;
}