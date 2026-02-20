#include <stdio.h>

int main() {
    printf("=== Good vs Bad Use of goto ===\n\n");
    
    // ✅ 良い例1: 多重ループからの脱出
    printf("GOOD Example 1: Escaping nested loops\n");
    int found = 0;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            for (int k = 0; k < 100; k++) {
                if (i * j * k == 1000) {
                    printf("Found: i=%d, j=%d, k=%d\n", i, j, k);
                    goto found_result;  // ✅ 3重ループから一気に脱出
                }
            }
        }
    }
    found_result:
    printf("This is acceptable use of goto\n\n");
    
    // ✅ 良い例2: エラー処理とクリーンアップ
    printf("GOOD Example 2: Error handling with cleanup\n");
    
    FILE* file = NULL;
    int* buffer = NULL;
    int success = 1;
    
    // 仮想的なエラーチェック
    int file_error = 0;
    int memory_error = 0;
    
    if (file_error) {
        printf("File open failed\n");
        goto cleanup;
    }
    
    if (memory_error) {
        printf("Memory allocation failed\n");
        goto cleanup;
    }
    
    printf("Processing data...\n");
    
    cleanup:
    printf("Cleaning up resources\n");
    // ここでファイルを閉じたり、メモリを解放したり
    printf("This is acceptable use of goto\n\n");
    
    // ❌ 悪い例1: スパゲッティコード
    printf("BAD Example 1: Spaghetti code (DON'T DO THIS)\n");
    printf("(Commented out - too confusing)\n");
    /*
    int x = 0;
    goto label2;
    
    label1:
    x++;
    goto label3;
    
    label2:
    x += 2;
    goto label1;
    
    label3:
    printf("x = %d\n", x);
    */
    printf("Code becomes unreadable!\n\n");
    
    // ❌ 悪い例2: ループの代わりに使う
    printf("BAD Example 2: Using goto as loop (DON'T DO THIS)\n");
    int counter = 0;
    
    loop_start:
    printf("%d ", counter);
    counter++;
    if (counter < 5) {
        goto loop_start;  // ❌ for文を使うべき
    }
    printf("\nUse for/while loop instead!\n\n");
    
    // ❌ 悪い例3: 変数のスコープを飛び越える
    printf("BAD Example 3: Jumping over variable initialization\n");
    printf("(This can cause undefined behavior)\n");
    
    int choice = 1;
    if (choice == 1) {
        goto skip_init;  // ❌ 変数の初期化を飛び越える
    }
    
    int important_var = 100;
    
    skip_init:
    // important_varが初期化されていない可能性がある
    printf("This is dangerous!\n\n");
    
    // 正しい方法の比較
    printf("COMPARISON: goto vs proper alternatives\n\n");
    
    printf("Scenario: Find first even number in nested array\n");
    int matrix[3][3] = {
        {1, 3, 5},
        {7, 9, 11},
        {13, 14, 15}
    };
    
    // goto版
    printf("Using goto: ");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (matrix[i][j] % 2 == 0) {
                printf("Found %d at [%d][%d]\n", matrix[i][j], i, j);
                goto done_goto;
            }
        }
    }
    done_goto:
    
    // フラグ版
    printf("Using flag: ");
    int found_flag = 0;
    for (int i = 0; i < 3 && !found_flag; i++) {
        for (int j = 0; j < 3; j++) {
            if (matrix[i][j] % 2 == 0) {
                printf("Found %d at [%d][%d]\n", matrix[i][j], i, j);
                found_flag = 1;
                break;
            }
        }
    }
    
    return 0;
}