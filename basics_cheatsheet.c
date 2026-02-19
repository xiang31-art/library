#include <stdio.h>

int main() {
    printf("=== C Language Basics Cheat Sheet ===\n\n");
    
    // データ型のサイズ
    printf("1. Data Type Sizes\n");
    printf("char: %zu bytes\n", sizeof(char));
    printf("int: %zu bytes\n", sizeof(int));
    printf("float: %zu bytes\n", sizeof(float));
    printf("double: %zu bytes\n\n", sizeof(double));
    
    // printf書式指定子
    printf("2. printf Format Specifiers\n");
    printf("%%d: integer (10進数)\n");
    printf("%%f: float/double (浮動小数点)\n");
    printf("%%c: character (文字)\n");
    printf("%%s: string (文字列)\n");
    printf("%%x: hexadecimal (16進数)\n");
    printf("%%o: octal (8進数)\n\n");
    
    // よく使う演算子
    printf("3. Common Operators\n");
    printf("Arithmetic: + - * / %%\n");
    printf("Comparison: == != < > <= >=\n");
    printf("Logical: && || !\n");
    printf("Assignment: = += -= *= /= %%=\n");
    printf("Increment/Decrement: ++ --\n\n");
    
    // 制御構文
    printf("4. Control Structures\n");
    printf("if (condition) { ... }\n");
    printf("else if (condition) { ... }\n");
    printf("else { ... }\n");
    printf("switch (variable) { case value: ... break; }\n");
    printf("for (init; condition; update) { ... }\n");
    printf("while (condition) { ... }\n");
    printf("do { ... } while (condition);\n\n");
    
    // 配列の基本
    printf("5. Array Basics\n");
    printf("Declaration: int arr[5];\n");
    printf("Initialization: int arr[5] = {1, 2, 3, 4, 5};\n");
    printf("Access: arr[0], arr[1], ...\n");
    printf("Size: sizeof(arr) / sizeof(arr[0])\n\n");
    
    // よくある間違い
    printf("6. Common Mistakes to Avoid\n");
    printf("X: if (x = 5) ... (assignment instead of comparison)\n");
    printf("O: if (x == 5) ... (correct comparison)\n\n");
    
    printf("X: for (int i = 0; i <= 5; i++) arr[i] (array out of bounds)\n");
    printf("O: for (int i = 0; i < 5; i++) arr[i] (correct range)\n\n");
    
    printf("X: printf(variable) (missing format specifier)\n");
    printf("O: printf(\"%%d\", variable) (correct format)\n\n");
    
    // 実用的なコードパターン
    printf("7. Useful Code Patterns\n\n");
    
    printf("Pattern 1: Swap two variables\n");
    int a = 5, b = 10;
    printf("Before: a=%d, b=%d\n", a, b);
    int temp = a;
    a = b;
    b = temp;
    printf("After: a=%d, b=%d\n\n", a, b);
    
    printf("Pattern 2: Find array sum\n");
    int numbers[] = {1, 2, 3, 4, 5};
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += numbers[i];
    }
    printf("Sum: %d\n\n", sum);
    
    printf("Pattern 3: Count occurrences\n");
    int data[] = {1, 2, 3, 2, 4, 2, 5};
    int target = 2;
    int count = 0;
    for (int i = 0; i < 7; i++) {
        if (data[i] == target) {
            count++;
        }
    }
    printf("Number %d appears %d times\n\n", target, count);
    
    return 0;
}