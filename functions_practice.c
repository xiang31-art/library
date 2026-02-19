#include <stdio.h>

// 課題用の関数プロトタイプ（あなたが実装してください）
int multiply(int a, int b);           // 課題1: 2つの数の掛け算
int isEven(int num);                  // 課題2: 偶数判定（偶数なら1、奇数なら0）
void printStars(int count);           // 課題3: 指定された数だけ星を表示
int factorial(int n);                 // 課題4: 階乗計算
int arraySum(int arr[], int size);    // 課題5: 配列の合計
int factorialx(int n);                // 課題4別解

int main() {
    printf("=== Functions Practice Exercises ===\n\n");
    
    // 課題1: 掛け算関数
    printf("Exercise 1: Multiplication function\n");
    printf("multiply(6, 7) = %d\n", multiply(6, 7));
    printf("multiply(3, 4) = %d\n\n", multiply(3, 4));
    
    // 課題2: 偶数判定関数
    printf("Exercise 2: Even number check function\n");
    printf("isEven(8) = %d (1=even, 0=odd)\n", isEven(8));
    printf("isEven(7) = %d (1=even, 0=odd)\n\n", isEven(7));
    
    // 課題3: 星を表示する関数
    printf("Exercise 3: Print stars function\n");
    printf("printStars(5): ");
    printStars(5);
    printf("printStars(3): ");
    printStars(3);
    printf("\n");
    
    // 課題4: 階乗計算関数
    printf("Exercise 4: Factorial function\n");
    printf("factorial(5) = %d\n", factorial(5));
    printf("factorial(4) = %d\n\n", factorial(4));
    
    // 課題5: 配列の合計関数
    printf("Exercise 5: Array sum function\n");
    int data[6] = {1, 2, 3, 4, 5, 6};
    printf("Array: ");
    for (int i = 0; i < 6; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
    printf("arraySum(data, 6) = %d\n", arraySum(data, 6));
    
    return 0;
}

// ここに関数を実装してください

// 課題1: 2つの数の掛け算
int multiply(int a, int b) {
    // ここにコードを書いてください
    int prod = 0;
    prod = a * b;
    return prod;
}

// 課題2: 偶数判定（偶数なら1、奇数なら0を返す）
int isEven(int num) {
    // ここにコードを書いてください
    if ((num % 2) == 0)
        return 1;
    else
        return 0;
}

// 課題3: 指定された数だけ星を表示
void printStars(int count){
    // ここにコードを書いてください
    for(int i = 0; i < count; i++){  // 修正: i < count
        printf("* ");
    }
    printf("\n");  // 修正: セミコロン追加
}   //メモ：return 値; だと、void関数は値を返せないのでエラー

// 課題4: 階乗計算（n! = n × (n-1) × ... × 1）
int factorial(int n) {
    // ここにコードを書いてください
    int factor = 1;
    for(int i = 1; i<=n; i++){
        factor *= i;
    }
    return factor;
}

//別解
int factorialx(int n){
    int factor = 1;
    
    if(n == 0)
        return 1;
    else{
        return n * factorialx(n - 1);
    }
    
}

// 課題5: 配列の全要素の合計
int arraySum(int arr[], int size) {
    // ここにコードを書いてください
    int sum = 0;
    for(int i = 0; i < size; i++){  // 修正: i < size
        sum += arr[i];
    }
    return sum;  // 修正: return文追加
}