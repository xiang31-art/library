#include <stdio.h>

int main() {
    printf("=== Forward Jump vs Backward Jump ===\n\n");
    
    // 前方ジャンプ（Forward Jump）
    printf("1. Forward Jump Example\n");
    int x = 10;
    
    if (x > 5) {
        printf("x is greater than 5\n");
        goto skip_code;  // 前方にジャンプ
    }
    
    printf("This code is skipped\n");
    x = 100;
    
    skip_code:
    printf("x = %d\n\n", x);  // x = 10
    
    // 後方ジャンプ（Backward Jump）
    printf("2. Backward Jump Example (Loop-like)\n");
    int count = 1;
    
    repeat:  // ラベル
    printf("Count: %d\n", count);
    count++;
    
    if (count <= 5) {
        goto repeat;  // 後方にジャンプ（ループのように動作）
    }
    
    printf("\n");
    
    // 注意: 後方ジャンプは無限ループになりやすい
    printf("3. Dangerous: Infinite loop risk\n");
    printf("(This example is commented out to prevent infinite loop)\n");
    /*
    dangerous_loop:
    printf("This will loop forever!\n");
    goto dangerous_loop;  // 無限ループ！
    */
    
    return 0;
}