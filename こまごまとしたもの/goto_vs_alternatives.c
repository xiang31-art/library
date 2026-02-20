#include <stdio.h>

int main() {
    printf("=== goto vs Alternative Methods ===\n\n");
    
    // ケース1: 多重ループからの脱出
    printf("Case 1: Escaping nested loops\n\n");
    
    // 方法A: goto文を使用
    printf("Method A: Using goto\n");
    for (int i = 1; i <= 5; i++) {
        for (int j = 1; j <= 5; j++) {
            printf("(%d,%d) ", i, j);
            if (i == 3 && j == 3) {
                goto exit_loops_A;
            }
        }
        printf("\n");
    }
    exit_loops_A:
    printf("\nExited using goto\n\n");
    
    // 方法B: フラグ変数を使用
    printf("Method B: Using flag variable\n");
    int should_exit = 0;
    for (int i = 1; i <= 5 && !should_exit; i++) {
        for (int j = 1; j <= 5; j++) {
            printf("(%d,%d) ", i, j);
            if (i == 3 && j == 3) {
                should_exit = 1;
                break;
            }
        }
        printf("\n");
    }
    printf("Exited using flag\n\n");
    
    // ケース2: エラー処理
    printf("Case 2: Error handling\n\n");
    
    // 方法A: goto文を使用
    printf("Method A: Using goto for cleanup\n");
    int error_code = 0;
    int* data = NULL;
    
    // 仮想的な処理
    int step = 2;
    
    if (step == 1) {
        error_code = 1;
        goto cleanup_A;
    }
    
    if (step == 2) {
        error_code = 2;
        goto cleanup_A;
    }
    
    printf("All steps completed\n");
    
    cleanup_A:
    if (error_code) {
        printf("Error occurred at step %d\n", error_code);
    }
    printf("Cleanup completed\n\n");
    
    // 方法B: 関数を使用（最も推奨）
    printf("Method B: Using function (best practice)\n");
    printf("(See separate function example below)\n\n");
    
    // ケース3: 複雑な条件分岐
    printf("Case 3: Complex conditional logic\n\n");
    
    int value = 15;
    
    // 方法A: goto文
    printf("Method A: Using goto\n");
    if (value < 10) {
        goto case_small;
    } else if (value < 20) {
        goto case_medium;
    } else {
        goto case_large;
    }
    
    case_small:
    printf("Value is small: %d\n\n", value);
    goto end_switch;
    
    case_medium:
    printf("Value is medium: %d\n\n", value);
    goto end_switch;
    
    case_large:
    printf("Value is large: %d\n\n", value);
    
    end_switch:
    
    // 方法B: if-else（より読みやすい）
    printf("Method B: Using if-else (more readable)\n");
    if (value < 10) {
        printf("Value is small: %d\n", value);
    } else if (value < 20) {
        printf("Value is medium: %d\n", value);
    } else {
        printf("Value is large: %d\n", value);
    }
    
    return 0;
}