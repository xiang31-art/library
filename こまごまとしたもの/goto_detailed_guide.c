#include <stdio.h>

int main() {
    printf("=== goto Statement Detailed Guide ===\n\n");
    
    // 1. goto文の基本構文
    printf("1. Basic syntax of goto\n");
    printf("Starting...\n");
    
    goto skip_section;  // ラベルにジャンプ
    
    printf("This line will be skipped!\n");  // 実行されない
    
    skip_section:  // ラベル（コロンで終わる）
    printf("Jumped to skip_section label\n\n");
    
    // 2. 前方ジャンプと後方ジャンプ
    printf("2. Forward jump vs Backward jump\n");
    
    int counter = 0;
    
    loop_start:  // ラベル
    printf("Counter: %d\n", counter);
    counter++;
    
    if (counter < 3) {
        goto loop_start;  // 後方ジャンプ（ループのように動作）
    }
    printf("\n");
    
    // 3. 多重ループからの脱出（最も実用的な使い方）
    printf("3. Escaping from nested loops\n");
    printf("Finding pair where i*j = 12:\n");
    
    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 10; j++) {
            if (i * j == 12) {
                printf("Found: i=%d, j=%d\n", i, j);
                goto found;  // 全てのループから一気に脱出
            }
        }
    }
    
    found:
    printf("Search completed\n\n");
    
    // 4. エラー処理での使用例
    printf("4. Error handling with goto\n");
    
    int value = 5;
    
    if (value < 0) {
        printf("Error: Negative value\n");
        goto error_handler;
    }
    
    if (value > 100) {
        printf("Error: Value too large\n");
        goto error_handler;
    }
    
    printf("Value is valid: %d\n", value);
    goto cleanup;  // 正常終了時はクリーンアップへ
    
    error_handler:
    printf("Handling error...\n");
    
    cleanup:
    printf("Cleanup completed\n\n");
    
    // 5. goto文を使わない代替方法
    printf("5. Alternative without goto (using flag)\n");
    
    int found_flag = 0;
    for (int i = 1; i <= 10 && !found_flag; i++) {
        for (int j = 1; j <= 10; j++) {
            if (i * j == 20) {
                printf("Found: i=%d, j=%d\n", i, j);
                found_flag = 1;
                break;
            }
        }
    }
    printf("Search completed\n");
    
    return 0;
}