#include <stdio.h>

int main() {
    printf("=== Array Maximum Value - Detailed Explanation ===\n\n");
    
    // 1. 問題の設定
    printf("1. Problem Setup\n");
    int data[5] = {23, 45, 12, 67, 34};
    printf("Array: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
    printf("Goal: Find the maximum value in this array\n\n");
    
    // 2. 間違った方法（あなたの最初のコード）
    printf("2. Wrong Approach (Initial Code)\n");
    int max_wrong = 0;  // ❌ 0で初期化
    printf("Initial max = %d\n", max_wrong);
    
    for (int i = 0; i < 5; i++) {
        printf("Step %d: Comparing max(%d) with data[%d](%d)\n", 
               i+1, max_wrong, i, data[i]);
        
        if (max_wrong < data[i]) {
            max_wrong = data[i];
            printf("  → max updated to %d\n", max_wrong);
        } else {
            printf("  → max remains %d\n", max_wrong);
        }
    }
    printf("Result: %d\n\n", max_wrong);
    
    // 3. 正しい方法
    printf("3. Correct Approach\n");
    int max_correct = data[0];  // ✅ 最初の要素で初期化
    printf("Initial max = data[0] = %d\n", max_correct);
    
    for (int i = 1; i < 5; i++) {  // i=1から開始
        printf("Step %d: Comparing max(%d) with data[%d](%d)\n", 
               i, max_correct, i, data[i]);
        
        if (max_correct < data[i]) {
            max_correct = data[i];
            printf("  → max updated to %d\n", max_correct);
        } else {
            printf("  → max remains %d\n", max_correct);
        }
    }
    printf("Result: %d\n\n", max_correct);
    
    // 4. なぜ0で初期化するとダメなのか？
    printf("4. Why initializing with 0 is problematic?\n");
    
    // 例1: 全て負数の配列
    int negative_array[4] = {-10, -5, -20, -3};
    printf("Example 1: All negative numbers\n");
    printf("Array: ");
    for (int i = 0; i < 4; i++) {
        printf("%d ", negative_array[i]);
    }
    printf("\n");
    
    // 間違った方法
    int max_neg_wrong = 0;
    for (int i = 0; i < 4; i++) {
        if (max_neg_wrong < negative_array[i]) {
            max_neg_wrong = negative_array[i];
        }
    }
    printf("Wrong method (init with 0): %d ❌\n", max_neg_wrong);
    
    // 正しい方法
    int max_neg_correct = negative_array[0];
    for (int i = 1; i < 4; i++) {
        if (max_neg_correct < negative_array[i]) {
            max_neg_correct = negative_array[i];
        }
    }
    printf("Correct method (init with first element): %d ✅\n\n", max_neg_correct);
    
    // 5. 別のアプローチ方法
    printf("5. Alternative Approaches\n");
    
    // 方法A: すべての要素をチェック（i=0から）
    printf("Method A: Check all elements (i=0 to n-1)\n");
    int max_A = data[0];
    for (int i = 0; i < 5; i++) {  // i=0から開始
        if (max_A < data[i]) {
            max_A = data[i];
        }
    }
    printf("Result: %d\n", max_A);
    
    // 方法B: 最初の要素をスキップ（i=1から）
    printf("Method B: Skip first element (i=1 to n-1)\n");
    int max_B = data[0];
    for (int i = 1; i < 5; i++) {  // i=1から開始
        if (max_B < data[i]) {
            max_B = data[i];
        }
    }
    printf("Result: %d\n\n", max_B);
    
    return 0;
}