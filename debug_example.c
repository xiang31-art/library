#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// ========================================
// デバッグマクロの定義
// ========================================
#define DEBUG 1

#if DEBUG
    #define DEBUG_PRINT(fmt, ...) \
        printf("DEBUG [%s:%d]: " fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#else
    #define DEBUG_PRINT(fmt, ...) // 何もしない
#endif

// ========================================
// メモリ追跡用のカウンタ
// ========================================
static int malloc_count = 0;
static int free_count = 0;

void *debug_malloc(size_t size) {
    void *ptr = malloc(size);
    malloc_count++;
    DEBUG_PRINT("malloc #%d (%zu bytes) at %p\n", malloc_count, size, ptr);
    return ptr;
}

void debug_free(void *ptr) {
    free_count++;
    DEBUG_PRINT("free #%d at %p\n", free_count, ptr);
    free(ptr);
}

void check_memory_leaks() {
    printf("\n=== メモリチェック ===\n");
    printf("malloc 呼び出し: %d\n", malloc_count);
    printf("free 呼び出し: %d\n", free_count);
    if (malloc_count != free_count) {
        printf("WARNING: メモリリークの可能性があります！\n");
    } else {
        printf("OK: メモリリークはありません\n");
    }
}

// ========================================
// 例1：ポインタのデバッグ
// ========================================
void pointer_debug_example() {
    printf("\n=== ポインタのデバッグ例 ===\n");
    
    int value = 42;
    int *ptr = &value;
    
    // ポインタの情報を出力
    DEBUG_PRINT("ptr のアドレス: %p\n", (void*)ptr);
    DEBUG_PRINT("ptr が指す値: %d\n", *ptr);
    
    // NULL チェックの例
    int *null_ptr = NULL;
    DEBUG_PRINT("null_ptr のアドレス: %p\n", (void*)null_ptr);
    
    if (null_ptr != NULL) {
        printf("値: %d\n", *null_ptr);
    } else {
        printf("null_ptr は NULL です\n");
    }
}

// ========================================
// 例2：配列のデバッグ
// ========================================
void array_debug_example() {
    printf("\n=== 配列のデバッグ例 ===\n");
    
    int arr[5] = {10, 20, 30, 40, 50};
    
    // 配列の内容を出力
    for (int i = 0; i < 5; i++) {
        DEBUG_PRINT("arr[%d] = %d\n", i, arr[i]);
    }
    
    // 境界チェックの例
    int index = 5;
    DEBUG_PRINT("アクセスしようとしているインデックス: %d\n", index);
    
    if (index >= 0 && index < 5) {
        printf("arr[%d] = %d\n", index, arr[index]);
    } else {
        printf("ERROR: インデックス %d は範囲外です（0-4が有効）\n", index);
    }
}

// ========================================
// 例3：メモリ管理のデバッグ
// ========================================
void memory_debug_example() {
    printf("\n=== メモリ管理のデバッグ例 ===\n");
    
    // メモリ割り当て
    int *data = debug_malloc(sizeof(int) * 10);
    
    if (data == NULL) {
        printf("ERROR: メモリ割り当て失敗\n");
        return;
    }
    
    // データの使用
    for (int i = 0; i < 10; i++) {
        data[i] = i * 10;
        DEBUG_PRINT("data[%d] = %d\n", i, data[i]);
    }
    
    // メモリ解放
    debug_free(data);
}

// ========================================
// 例4：関数のデバッグ
// ========================================
int divide_with_debug(int a, int b) {
    DEBUG_PRINT("divide_with_debug 呼び出し: a=%d, b=%d\n", a, b);
    
    // 入力値の検証
    if (b == 0) {
        printf("ERROR: ゼロ除算が発生しました\n");
        return 0;
    }
    
    int result = a / b;
    DEBUG_PRINT("結果: %d\n", result);
    
    return result;
}

void function_debug_example() {
    printf("\n=== 関数のデバッグ例 ===\n");
    
    int result1 = divide_with_debug(10, 2);
    printf("10 / 2 = %d\n", result1);
    
    int result2 = divide_with_debug(10, 0);
    printf("10 / 0 = %d\n", result2);
}

// ========================================
// メイン関数
// ========================================
int main() {
    printf("╔════════════════════════════════════════════════════════╗\n");
    printf("║           C言語デバッグ実践例                         ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n");
    
    pointer_debug_example();
    array_debug_example();
    memory_debug_example();
    function_debug_example();
    
    check_memory_leaks();
    
    printf("\n=== プログラム終了 ===\n");
    return 0;
}
