#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// ========================================
// シグナルハンドラ（Windows では限定的）
// ========================================
void signal_handler(int sig) {
    printf("\n=== シグナルを受信しました ===\n");
    printf("シグナル番号: %d\n", sig);
    
    if (sig == SIGSEGV) {
        printf("SIGSEGV: セグメンテーションフォルト（不正なメモリアクセス）\n");
    } else if (sig == SIGABRT) {
        printf("SIGABRT: プログラムの異常終了\n");
    }
    
    printf("プログラムを終了します\n");
    exit(1);
}

// ========================================
// テスト1: NULL ポインタへのアクセス
// ========================================
void test_null_pointer() {
    printf("\n--- テスト1: NULL ポインタへのアクセス ---\n");
    int *ptr = NULL;
    printf("NULL ポインタに値を書き込もうとします...\n");
    *ptr = 10;  // ここでクラッシュ
    printf("この行は実行されません\n");
}

// ========================================
// テスト2: 初期化されていないポインタ
// ========================================
void test_uninitialized_pointer() {
    printf("\n--- テスト2: 初期化されていないポインタ ---\n");
    int *ptr;  // 初期化されていない
    printf("初期化されていないポインタに値を書き込もうとします...\n");
    *ptr = 10;  // ここでクラッシュ
    printf("この行は実行されません\n");
}

// ========================================
// テスト3: 解放済みメモリへのアクセス
// ========================================
void test_use_after_free() {
    printf("\n--- テスト3: 解放済みメモリへのアクセス ---\n");
    int *ptr = malloc(sizeof(int));
    *ptr = 42;
    printf("メモリを解放します...\n");
    free(ptr);
    printf("解放済みメモリに値を書き込もうとします...\n");
    *ptr = 10;  // ここでクラッシュ（または不正な動作）
    printf("この行は実行されません\n");
}

// ========================================
// テスト4: 配列の境界外アクセス
// ========================================
void test_buffer_overflow() {
    printf("\n--- テスト4: 配列の境界外アクセス ---\n");
    int arr[5] = {1, 2, 3, 4, 5};
    printf("配列の範囲外にアクセスしようとします...\n");
    // 大きく範囲外にアクセス
    arr[1000000] = 10;  // ここでクラッシュする可能性
    printf("この行は実行されません（または実行される場合もある）\n");
}

// ========================================
// テスト5: スタックオーバーフロー
// ========================================
void recursive_function(int n) {
    int large_array[10000];  // スタックに大きな配列を確保
    large_array[0] = n;
    printf("再帰レベル: %d\n", n);
    recursive_function(n + 1);  // 無限再帰
}

void test_stack_overflow() {
    printf("\n--- テスト5: スタックオーバーフロー ---\n");
    printf("無限再帰を開始します...\n");
    recursive_function(0);
    printf("この行は実行されません\n");
}

// ========================================
// メイン関数
// ========================================
int main() {
    printf("╔════════════════════════════════════════════════════════╗\n");
    printf("║     MinGW でのセグメンテーションフォルトテスト        ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n");
    
    // シグナルハンドラを設定（Windows では限定的）
    signal(SIGSEGV, signal_handler);
    signal(SIGABRT, signal_handler);
    
    printf("\n警告: このプログラムは意図的にクラッシュします\n");
    printf("どのテストを実行しますか？\n");
    printf("1: NULL ポインタへのアクセス\n");
    printf("2: 初期化されていないポインタ\n");
    printf("3: 解放済みメモリへのアクセス\n");
    printf("4: 配列の境界外アクセス\n");
    printf("5: スタックオーバーフロー\n");
    printf("0: 終了\n");
    printf("選択: ");
    
    int choice;
    scanf("%d", &choice);
    
    switch (choice) {
        case 1:
            test_null_pointer();
            break;
        case 2:
            test_uninitialized_pointer();
            break;
        case 3:
            test_use_after_free();
            break;
        case 4:
            test_buffer_overflow();
            break;
        case 5:
            test_stack_overflow();
            break;
        case 0:
            printf("プログラムを終了します\n");
            break;
        default:
            printf("無効な選択です\n");
    }
    
    printf("\n=== プログラムが正常に終了しました ===\n");
    return 0;
}
