#include <stdio.h>

// 関数プロトタイプ
void swap(int *a, int *b);
void doubleValue(int *num);
int findMax(int *arr, int size);
void reverseArray(int *arr, int size);
void printArray(int *arr, int size);

int main() {
    printf("=== ポインタ練習問題（穴埋め形式） ===\n\n");
    
    // 課題1: swap関数
    printf("課題1: ポインタを使って2つの値を交換\n");
    int x = 10, y = 20;
    printf("交換前: x = %d, y = %d\n", x, y);
    swap(&x, &y);
    printf("交換後: x = %d, y = %d\n\n", x, y);
    
    // 課題2: doubleValue関数
    printf("課題2: ポインタを使って値を2倍にする\n");
    int num = 15;
    printf("変更前: num = %d\n", num);
    doubleValue(&num);
    printf("変更後: num = %d\n\n", num);
    
    // 課題3: findMax関数
    printf("課題3: ポインタを使って配列の最大値を見つける\n");
    int data[6] = {23, 45, 12, 67, 34, 56};
    printf("配列: ");
    printArray(data, 6);
    int max = findMax(data, 6);
    printf("最大値: %d\n\n", max);
    
    // 課題4: reverseArray関数
    printf("課題4: ポインタを使って配列を逆順にする\n");
    int original[5] = {1, 2, 3, 4, 5};
    printf("元の配列: ");
    printArray(original, 5);
    reverseArray(original, 5);
    printf("逆順配列: ");
    printArray(original, 5);
    
    return 0;
}

// ========================================
// ここから下の関数を完成させてください
// ========================================

// 課題1: 2つの値を交換する関数
// ヒント: 一時変数tempを使って、*aと*bの値を交換します
void swap(int *a, int *b) {
    // ここにプログラムを書いてください
    int temp = 0;
    temp = *a;
    *a = *b;
    *b = temp;
}

// 課題2: 値を2倍にする関数
// ヒント: *numを使ってポインタが指す値を変更します
void doubleValue(int *num) {
    // ここにプログラムを書いてください
    *num *= 2;
}

// 課題3: 配列の最大値を見つける関数
// ヒント: *(arr + i) でi番目の要素にアクセスできます
int findMax(int *arr, int size) {
    // ここにプログラムを書いてください
    int max = *(arr + 0);
    for(int i = 1; i < size; i++){
        if(max < *(arr + i)){
            max = *(arr + i);
        }
    }
    return max;
}

// 課題4: 配列を逆順にする関数
// ヒント: 配列の前半と後半を交換します。size/2回ループします
void reverseArray(int *arr, int size) {
    // ここにプログラムを書いてください
    int temp = 0;
    for(int i = 0; i < (size / 2); i++){
        temp = *(arr + i);
        *(arr + i) = *(arr + (size - 1 - i));
        *(arr + (size - 1 - i)) = temp;
    }
}

// 補助関数: 配列を表示（完成版）
void printArray(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", *(arr + i));
    }
    printf("\n");
}

/*
========================================
ポイント:
========================================
1. ポインタの宣言: int *p;
2. アドレス取得: &変数名
3. 値の取得（デリファレンス）: *ポインタ名
4. 配列とポインタ: arr[i] と *(arr + i) は同じ
5. 関数でポインタを使うと、元の変数を直接変更できる

========================================
解答例:
========================================

// 課題1: swap関数
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 課題2: doubleValue関数
void doubleValue(int *num) {
    *num *= 2;
    // または: *num = *num * 2;
}

// 課題3: findMax関数
int findMax(int *arr, int size) {
    int max = *(arr + 0);  // または *arr
    for(int i = 1; i < size; i++) {
        if(max < *(arr + i)) {
            max = *(arr + i);
        }
    }
    return max;
}

// 課題4: reverseArray関数
void reverseArray(int *arr, int size) {
    int temp = 0;
    for(int i = 0; i < (size / 2); i++) {
        temp = *(arr + i);
        *(arr + i) = *(arr + (size - 1 - i));
        *(arr + (size - 1 - i)) = temp;
    }
}

*/
