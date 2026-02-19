#include <stdio.h>

int main() {
    printf("=== Basics Practice Exercises ===\n\n");
    
    // 課題1: 変数の宣言と計算
    printf("Exercise 1: Variables and Calculation\n");
    printf("Declare variables for length and width, calculate area\n");
    // ここにコードを書いてください
    int length = 3;
    int width = 4;
    int area = 0;
    area = length * width;  // 修正: 掛け算
    printf("Area: %d\n\n", area);  // 修正: \n\n
    // int length = ?;
    // int width = ?;
    // int area = ?;
    // printf("Area: %d\n\n", area);
    
    
    
    // 課題2: 偶数・奇数の判定
    printf("Exercise 2: Even or Odd\n");
    printf("Check if number 17 is even or odd\n");
    // ここにコードを書いてください
    int num =17;
    if((num % 2) == 0){
        printf("num = %d →even number\n",num);
    }
    else{
        printf("num = %d →odd number\n",num);
    }
    // int num = 17;
    // if (...) { ... }
    
    
    printf("\n");
    
    // 課題3: 1から10までの合計
    printf("Exercise 3: Sum from 1 to 10\n");
    printf("Calculate sum using for loop\n");
    // ここにコードを書いてください
    int sum = 0;
    for(int i=1; i<=10; i++){
        sum += i;
    }
    printf("Sum: %d\n\n",sum);
    // int sum = 0;
    // for (...) { ... }
    // printf("Sum: %d\n\n", sum);
    
    
    
    // 課題4: 配列の最大値を見つける
    printf("Exercise 4: Find maximum value in array\n");
    int data[5] = {23, 45, 12, 67, 34};
    printf("Array: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
    // ここに最大値を見つけるコードを書いてください
    int max = data[0];  // 修正: 最初の要素で初期化
    for(int i=1; i<5; i++){  // 修正: i=1から開始
        if(max < data[i]){
            max = data[i];
        }
    }
    printf("Maximum: %d\n\n", max);

    // int max = data[0];
    // for (...) { ... }
    // printf("Maximum: %d\n\n", max);
    
    
    
    // 課題5: 九九の一部を表示
    printf("Exercise 5: Multiplication table (5 times table)\n");
    printf("Display 5 x 1 to 5 x 9\n");
    // ここにコードを書いてください
    // for (int i = 1; i <= 9; i++) { ... }
    for(int i = 1; i <= 9; i++){
        printf("5 x %d = %d\n",i,i*5);
    }
    printf("\n");
    
    // 課題6: 文字列の各文字を表示
    printf("Exercise 6: Display each character in string\n");
    char word[] = "Hello";
    printf("String: %s\n", word);
    printf("Characters: ");
    // ここにコードを書いてください
    // for (int i = 0; word[i] != '\0'; i++) { ... }
    for(int i = 0; word[i] != '\0'; i++){
        printf("%c ",word[i]);
    }
    
    printf("\n");
    
    return 0;
}