#include <stdio.h>

int main() {
    printf("=== Comparison: Different Initialization Methods ===\n\n");
    
    // テストケース1: 正の数のみ
    printf("Test Case 1: Positive numbers only\n");
    int test1[4] = {5, 12, 8, 15};
    printf("Array: [5, 12, 8, 15]\n");
    printf("Expected maximum: 15\n\n");
    
    // 方法1: max = 0
    int max1 = 0;
    for (int i = 0; i < 4; i++) {
        if (max1 < test1[i]) max1 = test1[i];
    }
    printf("Method 1 (max = 0): %d %s\n", max1, (max1 == 15) ? "✅" : "❌");
    
    // 方法2: max = array[0]
    int max2 = test1[0];
    for (int i = 1; i < 4; i++) {
        if (max2 < test1[i]) max2 = test1[i];
    }
    printf("Method 2 (max = array[0]): %d %s\n\n", max2, (max2 == 15) ? "✅" : "❌");
    
    // テストケース2: 負の数のみ
    printf("Test Case 2: Negative numbers only\n");
    int test2[4] = {-5, -12, -8, -15};
    printf("Array: [-5, -12, -8, -15]\n");
    printf("Expected maximum: -5\n\n");
    
    // 方法1: max = 0
    int max3 = 0;
    for (int i = 0; i < 4; i++) {
        if (max3 < test2[i]) max3 = test2[i];
    }
    printf("Method 1 (max = 0): %d %s\n", max3, (max3 == -5) ? "✅" : "❌");
    
    // 方法2: max = array[0]
    int max4 = test2[0];
    for (int i = 1; i < 4; i++) {
        if (max4 < test2[i]) max4 = test2[i];
    }
    printf("Method 2 (max = array[0]): %d %s\n\n", max4, (max4 == -5) ? "✅" : "❌");
    
    // テストケース3: 混合（正と負）
    printf("Test Case 3: Mixed positive and negative\n");
    int test3[5] = {-3, 7, -1, 4, -8};
    printf("Array: [-3, 7, -1, 4, -8]\n");
    printf("Expected maximum: 7\n\n");
    
    // 方法1: max = 0
    int max5 = 0;
    for (int i = 0; i < 5; i++) {
        if (max5 < test3[i]) max5 = test3[i];
    }
    printf("Method 1 (max = 0): %d %s\n", max5, (max5 == 7) ? "✅" : "❌");
    
    // 方法2: max = array[0]
    int max6 = test3[0];
    for (int i = 1; i < 5; i++) {
        if (max6 < test3[i]) max6 = test3[i];
    }
    printf("Method 2 (max = array[0]): %d %s\n\n", max6, (max6 == 7) ? "✅" : "❌");
    
    // 結論
    printf("=== Conclusion ===\n");
    printf("Method 1 (max = 0): Works only when array contains positive numbers\n");
    printf("Method 2 (max = array[0]): Always works correctly\n");
    printf("Recommendation: Always use max = array[0]\n");
    
    return 0;
}