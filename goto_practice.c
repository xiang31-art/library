#include <stdio.h>

int main() {
    printf("=== goto Practice Exercises ===\n\n");
    
    // 課題1: 以下のコードの出力を予測してください
    printf("Exercise 1: Predict the output\n");
    int a = 0;
    
    goto label_B;
    
    label_A:
    printf("Label A: a = %d\n", a);
    goto label_C;
    
    label_B:
    a = 10;
    printf("Label B: a = %d\n", a);
    goto label_A;
    
    label_C:
    printf("Label C: a = %d\n", a);
    printf("\n");
    
    // 課題2: このコードをgoto文を使わずに書き直してください
    printf("Exercise 2: Rewrite without goto\n");
    printf("Original code with goto:\n");
    
    int x = 5;
    if (x < 0) {
        goto negative;
    } else if (x == 0) {
        goto zero;
    } else {
        goto positive;
    }
    
    negative:
    printf("x is negative\n");
    goto end;
    
    zero:
    printf("x is zero\n");
    goto end;
    
    positive:
    printf("x is positive\n");
    
    end:
    printf("\n");
    
    // 課題3: 3重ループから脱出する2つの方法を実装
    printf("Exercise 3: Implement two methods to escape triple loop\n");
    
    // 方法1: goto文
    printf("Method 1 (goto): ");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 5; k++) {
                if (i + j + k == 6) {
                    printf("Found at (%d,%d,%d)\n", i, j, k);
                    goto triple_exit;
                }
            }
        }
    }
    triple_exit:
    
    // 方法2: フラグ変数（あなたが実装してください）
    printf("Method 2 (flag): ");
    // ここにコードを書いてください
    
    
    printf("\n");
    
    // 課題4: このgoto文の使い方は適切か判断してください
    printf("Exercise 4: Is this goto usage appropriate?\n");
    
    int count = 0;
    start_loop:
    printf("%d ", count);
    count++;
    if (count < 5) {
        goto start_loop;
    }
    printf("\n");
    printf("Answer: This should use a for/while loop instead\n");
    
    return 0;
}