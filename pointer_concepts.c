#include <stdio.h>

int main() {
    printf("=== Key Pointer Concepts ===\n\n");
    
    // 1. &演算子と*演算子の違い
    printf("1. Address-of (&) vs Dereference (*) Operators\n");
    
    int x = 15;
    int *p = &x;
    
    printf("Variable x = %d\n", x);
    printf("Address of x (&x) = %p\n", &x);
    printf("Pointer p = %p\n", p);
    printf("Value pointed by p (*p) = %d\n", *p);
    printf("Address of pointer p (&p) = %p\n\n", &p);
    
    // 2. ポインタの型の重要性
    printf("2. Importance of Pointer Types\n");
    
    int int_var = 1000;
    float float_var = 3.14f;
    char char_var = 'A';
    
    int *int_ptr = &int_var;
    float *float_ptr = &float_var;
    char *char_ptr = &char_var;
    
    printf("int_var = %d, *int_ptr = %d\n", int_var, *int_ptr);
    printf("float_var = %.2f, *float_ptr = %.2f\n", float_var, *float_ptr);
    printf("char_var = %c, *char_ptr = %c\n\n", char_var, *char_ptr);
    
    // 3. ポインタ演算
    printf("3. Pointer Arithmetic\n");
    
    int numbers[4] = {100, 200, 300, 400};
    int *num_ptr = numbers;
    
    printf("Array: ");
    for (int i = 0; i < 4; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    
    printf("Using pointer arithmetic:\n");
    for (int i = 0; i < 4; i++) {
        printf("*(num_ptr + %d) = %d (address: %p)\n", 
               i, *(num_ptr + i), (num_ptr + i));
    }
    printf("\n");
    
    // 4. ポインタの比較
    printf("4. Pointer Comparison\n");
    
    int a = 10, b = 20;
    int *ptr_a = &a;
    int *ptr_b = &b;
    int *ptr_a2 = &a;
    
    printf("ptr_a == ptr_b: %s\n", (ptr_a == ptr_b) ? "true" : "false");
    printf("ptr_a == ptr_a2: %s\n", (ptr_a == ptr_a2) ? "true" : "false");
    printf("*ptr_a == *ptr_b: %s\n", (*ptr_a == *ptr_b) ? "true" : "false");
    
    return 0;
}