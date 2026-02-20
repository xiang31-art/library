#include <stdio.h>

int main() {
    printf("=== C Language Basics Review ===\n\n");
    
    // 1. 変数の宣言と初期化
    printf("1. Variables and Data Types\n");
    
    int age = 20;                    // 整数型
    float height = 170.5;            // 浮動小数点型
    char grade = 'A';                // 文字型
    double pi = 3.14159265359;       // 倍精度浮動小数点型
    
    printf("int: %d\n", age);
    printf("float: %.1f\n", height);
    printf("char: %c\n", grade);
    printf("double: %.10f\n\n", pi);
    
    // 2. 算術演算子
    printf("2. Arithmetic Operators\n");
    
    int a = 10, b = 3;
    printf("%d + %d = %d\n", a, b, a + b);    // 加算
    printf("%d - %d = %d\n", a, b, a - b);    // 減算
    printf("%d * %d = %d\n", a, b, a * b);    // 乗算
    printf("%d / %d = %d\n", a, b, a / b);    // 除算（整数）
    printf("%d %% %d = %d\n\n", a, b, a % b); // 剰余
    
    // 3. 比較演算子
    printf("3. Comparison Operators\n");
    
    int x = 5, y = 10;
    printf("%d == %d: %d\n", x, y, x == y);   // 等しい
    printf("%d != %d: %d\n", x, y, x != y);   // 等しくない
    printf("%d < %d: %d\n", x, y, x < y);     // より小さい
    printf("%d > %d: %d\n", x, y, x > y);     // より大きい
    printf("%d <= %d: %d\n", x, y, x <= y);   // 以下
    printf("%d >= %d: %d\n\n", x, y, x >= y); // 以上
    
    // 4. 論理演算子
    printf("4. Logical Operators\n");
    
    int true_val = 1, false_val = 0;
    printf("1 && 1 = %d (AND)\n", true_val && true_val);
    printf("1 && 0 = %d (AND)\n", true_val && false_val);
    printf("1 || 0 = %d (OR)\n", true_val || false_val);
    printf("0 || 0 = %d (OR)\n", false_val || false_val);
    printf("!1 = %d (NOT)\n", !true_val);
    printf("!0 = %d (NOT)\n\n", !false_val);
    
    // 5. if文の基本
    printf("5. if Statement\n");
    
    int score = 85;
    if (score >= 90) {
        printf("Grade: A\n");
    } else if (score >= 80) {
        printf("Grade: B\n");
    } else if (score >= 70) {
        printf("Grade: C\n");
    } else {
        printf("Grade: D\n");
    }
    printf("\n");
    
    // 6. switch文の基本
    printf("6. switch Statement\n");
    
    int day = 3;
    switch (day) {
        case 1:
            printf("Monday\n");
            break;
        case 2:
            printf("Tuesday\n");
            break;
        case 3:
            printf("Wednesday\n");
            break;
        default:
            printf("Other day\n");
    }
    printf("\n");
    
    // 7. for文の基本
    printf("7. for Loop\n");
    printf("Count 1 to 5: ");
    for (int i = 1; i <= 5; i++) {
        printf("%d ", i);
    }
    printf("\n\n");
    
    // 8. while文の基本
    printf("8. while Loop\n");
    printf("Count down from 5: ");
    int count = 5;
    while (count > 0) {
        printf("%d ", count);
        count--;
    }
    printf("\n\n");
    
    // 9. 配列の基本
    printf("9. Arrays\n");
    
    int numbers[5] = {10, 20, 30, 40, 50};
    printf("Array elements: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n\n");
    
    // 10. 文字列の基本
    printf("10. Strings\n");
    
    char name[] = "Alice";
    printf("Name: %s\n", name);
    printf("First character: %c\n", name[0]);
    printf("String length: %d\n\n", 5);
    
    return 0;
}