#include <stdio.h>

int main() {
    printf("=== Ternary Operator (Conditional Operator) Guide ===\n\n");
    
    // 1. 基本構文
    printf("1. Basic Syntax\n");
    printf("Format: condition ? value_if_true : value_if_false\n\n");
    
    // 2. 簡単な例
    printf("2. Simple Examples\n");
    
    int a = 10, b = 5;
    
    // 三項演算子を使用
    char* result1 = (a > b) ? "a is larger" : "b is larger";
    printf("a = %d, b = %d\n", a, b);
    printf("Using ternary: %s\n", result1);
    
    // 同じことをif-else文で書くと
    char* result2;
    if (a > b) {
        result2 = "a is larger";
    } else {
        result2 = "b is larger";
    }
    printf("Using if-else: %s\n\n", result2);
    
    // 3. 数値での例
    printf("3. Numeric Examples\n");
    
    int x = 15;
    int max_value = 10;
    
    // 三項演算子で値を選択
    int selected = (x > max_value) ? x : max_value;
    printf("x = %d, max_value = %d\n", x, max_value);
    printf("Selected value: %d\n", selected);
    
    // 三項演算子で文字を選択
    char grade = (x >= 60) ? 'P' : 'F';  // Pass or Fail
    printf("Grade for score %d: %c\n\n", x, grade);
    
    // 4. あなたが質問したコードの解説
    printf("4. Your Question: (max == 15) ? \"✅\" : \"❌\"\n");
    
    int max = 15;
    int expected = 15;
    
    printf("max = %d, expected = %d\n", max, expected);
    printf("Condition: (max == expected) = (%d == %d) = %s\n", 
           max, expected, (max == expected) ? "true" : "false");
    
    // ステップバイステップ解説
    printf("\nStep by step:\n");
    printf("1. Evaluate condition: (15 == 15) → true (1)\n");
    printf("2. Since true, return first value: \"✅\"\n");
    printf("3. Result: %s\n\n", (max == expected) ? "✅" : "❌");
    
    // 5. 複数の三項演算子の例
    printf("5. Multiple Conditions\n");
    
    int score = 85;
    char* letter_grade = (score >= 90) ? "A" :
                        (score >= 80) ? "B" :
                        (score >= 70) ? "C" :
                        (score >= 60) ? "D" : "F";
    
    printf("Score: %d → Grade: %s\n\n", score, letter_grade);
    
    // 6. 三項演算子 vs if-else の比較
    printf("6. Ternary vs if-else Comparison\n");
    
    int num = 7;
    
    // 三項演算子版（1行）
    printf("Ternary: %d is %s\n", num, (num % 2 == 0) ? "even" : "odd");
    
    // if-else版（5行）
    printf("if-else: %d is ", num);
    if (num % 2 == 0) {
        printf("even\n");
    } else {
        printf("odd\n");
    }
    
    printf("\n");
    
    // 7. 実用的な使用例
    printf("7. Practical Usage Examples\n");
    
    // 例1: 配列の境界チェック
    int array[5] = {10, 20, 30, 40, 50};
    int index = 3;
    int safe_value = (index >= 0 && index < 5) ? array[index] : -1;
    printf("Safe array access: array[%d] = %d\n", index, safe_value);
    
    // 例2: 最小値・最大値
    int val1 = 25, val2 = 18;
    int minimum = (val1 < val2) ? val1 : val2;
    int maximum = (val1 > val2) ? val1 : val2;
    printf("min(%d, %d) = %d\n", val1, val2, minimum);
    printf("max(%d, %d) = %d\n", val1, val2, maximum);
    
    // 例3: 絶対値
    int negative_num = -42;
    int absolute = (negative_num < 0) ? -negative_num : negative_num;
    printf("abs(%d) = %d\n", negative_num, absolute);
    
    return 0;
}