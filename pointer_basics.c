#include <stdio.h>

int main() {
    printf("=== Pointer Basics - Complete Guide ===\n\n");
    
    // 1. 変数とメモリアドレスの基本概念
    printf("1. Variables and Memory Addresses\n");
    
    int number = 42;
    printf("Variable: number = %d\n", number);
    printf("Address of number: %p\n", &number);  // &演算子でアドレス取得
    printf("Size of int: %zu bytes\n\n", sizeof(int));
    
    // 2. ポインタの宣言と初期化
    printf("2. Pointer Declaration and Initialization\n");
    
    int *ptr;  // ポインタの宣言
    ptr = &number;  // ポインタに変数のアドレスを代入
    
    printf("Pointer ptr points to address: %p\n", ptr);
    printf("Value at that address: %d\n", *ptr);  // *演算子で値を取得
    printf("Address of pointer itself: %p\n\n", &ptr);
    
    // 3. ポインタを使った値の変更
    printf("3. Modifying Values Through Pointers\n");
    
    printf("Before: number = %d\n", number);
    *ptr = 100;  // ポインタ経由で値を変更
    printf("After: number = %d\n", number);
    printf("Changed through pointer!\n\n");
    
    // 4. 複数のポインタ
    printf("4. Multiple Pointers\n");
    
    int value = 25;
    int *ptr1 = &value;
    int *ptr2 = &value;  // 同じ変数を指す
    
    printf("value = %d\n", value);
    printf("*ptr1 = %d (address: %p)\n", *ptr1, ptr1);
    printf("*ptr2 = %d (address: %p)\n", *ptr2, ptr2);
    
    *ptr1 = 50;  // ptr1経由で変更
    printf("After *ptr1 = 50:\n");
    printf("value = %d, *ptr2 = %d\n\n", value, *ptr2);
    
    // 5. ポインタと配列
    printf("5. Pointers and Arrays\n");
    
    int arr[5] = {10, 20, 30, 40, 50};
    int *arr_ptr = arr;  // 配列名は最初の要素のアドレス
    
    printf("Array elements using array notation:\n");
    for (int i = 0; i < 5; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }
    
    printf("\nArray elements using pointer notation:\n");
    for (int i = 0; i < 5; i++) {
        printf("*(arr_ptr + %d) = %d\n", i, *(arr_ptr + i));
    }
    
    printf("\nPointer arithmetic:\n");
    printf("arr_ptr points to: %p (value: %d)\n", arr_ptr, *arr_ptr);
    arr_ptr++;  // 次の要素を指す
    printf("After arr_ptr++: %p (value: %d)\n", arr_ptr, *arr_ptr);
    
    return 0;
}