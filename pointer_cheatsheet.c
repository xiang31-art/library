#include <stdio.h>

int main() {
    printf("=== Pointer Cheat Sheet ===\n\n");
    
    // 基本的な演算子
    printf("1. Basic Operators\n");
    printf("&variable  → Get address of variable\n");
    printf("*pointer   → Get value at address (dereference)\n");
    printf("pointer++  → Move to next memory location\n");
    printf("pointer--  → Move to previous memory location\n\n");
    
    // 宣言の例
    printf("2. Declaration Examples\n");
    printf("int *ptr;        → Pointer to int\n");
    printf("float *fptr;     → Pointer to float\n");
    printf("char *cptr;      → Pointer to char\n");
    printf("int *arr_ptr;    → Pointer to int (can point to array)\n\n");
    
    // よくある間違い
    printf("3. Common Mistakes to Avoid\n");
    printf("❌ int *ptr; *ptr = 5;           → Using uninitialized pointer\n");
    printf("✅ int x = 0; int *ptr = &x;     → Initialize pointer first\n\n");
    
    printf("❌ int *ptr = 5;                 → Assigning value instead of address\n");
    printf("✅ int x = 5; int *ptr = &x;     → Assign address of variable\n\n");
    
    printf("❌ printf(\"%%d\", ptr);           → Printing address as integer\n");
    printf("✅ printf(\"%%p\", ptr);           → Use %%p for addresses\n");
    printf("✅ printf(\"%%d\", *ptr);          → Use *ptr for values\n\n");
    
    // 実用的なパターン
    printf("4. Useful Patterns\n");
    
    // パターン1: 関数で値を変更
    printf("Pattern 1: Modify value in function\n");
    int value = 10;
    printf("Before: value = %d\n", value);
    // 仮想的な関数呼び出し
    printf("Call: modifyValue(&value);\n");
    value = value * 2;  // 実際の変更をシミュレート
    printf("After: value = %d\n\n", value);
    
    // パターン2: 配列の処理
    printf("Pattern 2: Array processing\n");
    int arr[3] = {1, 2, 3};
    int *p = arr;
    printf("Array access methods:\n");
    printf("arr[0] = %d, *(p + 0) = %d, *p = %d\n", arr[0], *(p + 0), *p);
    printf("arr[1] = %d, *(p + 1) = %d, *(++p) = %d\n", arr[1], *(p + 1), *(++p));
    p = arr;  // リセット
    printf("\n");
    
    // パターン3: NULL ポインタチェック
    printf("Pattern 3: NULL pointer check\n");
    int *null_ptr = NULL;
    printf("Safe pointer usage:\n");
    printf("if (ptr != NULL) {\n");
    printf("    *ptr = value;  // Safe to use\n");
    printf("}\n\n");
    
    // メモリレイアウトの理解
    printf("5. Memory Layout Understanding\n");
    int a = 1, b = 2, c = 3;
    printf("Variables in memory:\n");
    printf("a = %d at address %p\n", a, &a);
    printf("b = %d at address %p\n", b, &b);
    printf("c = %d at address %p\n", c, &c);
    printf("Address difference: %ld bytes\n", (char*)&b - (char*)&a);
    
    return 0;
}