#include <stdio.h>

// 1. 関数の宣言（プロトタイプ）
void greet(void);                    // 引数なし、戻り値なし
int add(int a, int b);              // 引数あり、戻り値あり
int findMax(int arr[], int size);   // 配列を引数に取る関数
void printArray(int arr[], int size); // 配列を表示する関数

int main() {
    printf("=== Functions Basics ===\n\n");
    
    // 2. 関数の呼び出し
    printf("1. Function Calls\n");
    
    greet();  // 引数なしの関数呼び出し
    
    int result = add(5, 3);  // 戻り値を変数に格納
    printf("5 + 3 = %d\n\n", result);
    
    // 3. 配列を関数に渡す
    printf("2. Passing Arrays to Functions\n");
    
    int numbers[5] = {12, 45, 23, 67, 34};
    
    printf("Original array: ");
    printArray(numbers, 5);
    
    int maximum = findMax(numbers, 5);
    printf("Maximum value: %d\n\n", maximum);
    
    // 4. 関数を使った計算
    printf("3. Using Functions for Calculations\n");
    
    int x = 10, y = 20;
    printf("%d + %d = %d\n", x, y, add(x, y));
    printf("%d + %d = %d\n", 100, 200, add(100, 200));
    
    // 5. 関数の利点
    printf("\n4. Benefits of Functions\n");
    printf("- Code reusability\n");
    printf("- Better organization\n");
    printf("- Easier debugging\n");
    printf("- Modular programming\n");
    
    return 0;
}

// 関数の定義（実装）

// 挨拶を表示する関数
void greet(void) {
    printf("Hello from greet function!\n");
}

// 2つの数を足す関数
int add(int a, int b) {
    int sum = a + b;
    return sum;  // 結果を返す
}

// 配列の最大値を見つける関数
int findMax(int arr[], int size) {
    int max = arr[0];  // 最初の要素で初期化
    
    for (int i = 1; i < size; i++) {
        if (max < arr[i]) {
            max = arr[i];
        }
    }
    
    return max;  // 最大値を返す
}

// 配列を表示する関数
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}