#include <stdio.h>

// 関数プロトタイプ
void swap(int *a, int *b);           // 課題1: 2つの値を交換
void doubleValue(int *num);          // 課題2: 値を2倍にする
int findMax(int *arr, int size);     // 課題3: 配列の最大値（ポインタ版）
void reverseArray(int *arr, int size); // 課題4: 配列を逆順にする
void printArray(int *arr, int size); // 補助関数: 配列表示

int main() {
    printf("=== Pointer Practice Exercises ===\n\n");
    
    // 課題1: swap関数
    printf("Exercise 1: Swap two values using pointers\n");
    int x = 10, y = 20;
    printf("Before swap: x = %d, y = %d\n", x, y);
    swap(&x, &y);
    printf("After swap: x = %d, y = %d\n\n", x, y);
    
    // 課題2: doubleValue関数
    printf("Exercise 2: Double a value using pointer\n");
    int num = 15;
    printf("Before: num = %d\n", num);
    doubleValue(&num);
    printf("After: num = %d\n\n", num);
    
    // 課題3: findMax関数（ポインタ版）
    printf("Exercise 3: Find maximum using pointers\n");
    int data[6] = {23, 45, 12, 67, 34, 56};
    printf("Array: ");
    printArray(data, 6);
    int max = findMax(data, 6);
    printf("Maximum value: %d\n\n", max);
    
    // 課題4: reverseArray関数
    printf("Exercise 4: Reverse array using pointers\n");
    int original[5] = {1, 2, 3, 4, 5};
    printf("Original array: ");
    printArray(original, 5);
    reverseArray(original, 5);
    printf("Reversed array: ");
    printArray(original, 5);
    
    return 0;
}

// ここに関数を実装してください

// 課題1: 2つの値を交換する関数
void swap(int *a, int *b) {
    // ここにコードを書いてください
    // ヒント: 一時変数を使って値を交換
    int temp = 0;
    temp = *a;
    *a = *b;
    *b = temp;
}

// 課題2: 値を2倍にする関数
void doubleValue(int *num) {
    // ここにコードを書いてください
    // ヒント: *num を使って値を変更
    *num *= 2;
}

// 課題3: 配列の最大値を見つける関数（ポインタ版）
int findMax(int *arr, int size) {
    // ここにコードを書いてください
    // ヒント: *(arr + i) または arr[i] を使用
    int max = *(arr + 0);
    for(int i = 1; i < size; i++){  // 修正: i < size
        if(max < *(arr + i)) {      // 修正: < に変更、括弧追加
            max = *(arr + i);
        }
    }
    return max;
}

// 課題4: 配列を逆順にする関数
void reverseArray(int *arr, int size) {
    // ここにコードを書いてください
    // ヒント: 最初と最後の要素を交換、次に2番目と後ろから2番目を交換...
    int temp = 0;
    for(int i = 0; i < (size / 2); i++){  // 修正: i < (size/2)
        temp = *(arr + i);
        *(arr + i) = *(arr + (size - 1 - i));  // 修正: size - 1 - i
        *(arr + (size - 1 - i)) = temp;
    }
}

// 補助関数: 配列を表示
void printArray(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", *(arr + i));
    }
    printf("\n");
}