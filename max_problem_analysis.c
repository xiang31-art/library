#include <stdio.h>

int main() {
    printf("=== Problem Analysis: Why max = 0 is wrong ===\n\n");
    
    // ケース1: 今回の配列（正の数のみ）
    printf("Case 1: Array with positive numbers\n");
    int data1[5] = {23, 45, 12, 67, 34};
    printf("Array: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", data1[i]);
    }
    printf("\n");
    
    int max1 = 0;
    printf("Starting with max = 0\n");
    for (int i = 0; i < 5; i++) {
        printf("  Check: 0 < %d? ", data1[i]);
        if (max1 < data1[i]) {
            max1 = data1[i];
            printf("Yes → max = %d\n", max1);
        } else {
            printf("No → max stays %d\n", max1);
        }
    }
    printf("Final result: %d (This works by luck!)\n\n", max1);
    
    // ケース2: 負の数を含む配列
    printf("Case 2: Array with negative numbers\n");
    int data2[5] = {-10, -5, -20, -3, -15};
    printf("Array: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", data2[i]);
    }
    printf("\n");
    
    int max2 = 0;
    printf("Starting with max = 0\n");
    for (int i = 0; i < 5; i++) {
        printf("  Check: 0 < %d? ", data2[i]);
        if (max2 < data2[i]) {
            max2 = data2[i];
            printf("Yes → max = %d\n", max2);
        } else {
            printf("No → max stays %d\n", max2);
        }
    }
    printf("Final result: %d ❌ (Wrong! Should be -3)\n\n", max2);
    
    // ケース3: 0より小さい正の数の配列
    printf("Case 3: Array with small positive numbers\n");
    int data3[4] = {0, 0, 0, 0};  // 全て0
    printf("Array: ");
    for (int i = 0; i < 4; i++) {
        printf("%d ", data3[i]);
    }
    printf("\n");
    
    int max3 = 0;
    printf("Starting with max = 0\n");
    for (int i = 0; i < 4; i++) {
        printf("  Check: 0 < %d? ", data3[i]);
        if (max3 < data3[i]) {
            max3 = data3[i];
            printf("Yes → max = %d\n", max3);
        } else {
            printf("No → max stays %d\n", max3);
        }
    }
    printf("Final result: %d (Correct, but only by coincidence)\n\n", max3);
    
    // 正しい方法の実演
    printf("=== Correct Method Demonstration ===\n\n");
    
    printf("Correct approach for Case 2 (negative numbers):\n");
    int correct_max = data2[0];  // 最初の要素で初期化
    printf("Starting with max = data[0] = %d\n", correct_max);
    
    for (int i = 1; i < 5; i++) {
        printf("  Check: %d < %d? ", correct_max, data2[i]);
        if (correct_max < data2[i]) {
            correct_max = data2[i];
            printf("Yes → max = %d\n", correct_max);
        } else {
            printf("No → max stays %d\n", correct_max);
        }
    }
    printf("Final result: %d ✅ (Correct!)\n\n", correct_max);
    
    return 0;
}