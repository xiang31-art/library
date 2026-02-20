#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ============================================
   エラーハンドリングの実例集
   ============================================ */

// エラーコード定義
typedef enum {
    SUCCESS = 0,
    ERROR_NULL_POINTER = -1,
    ERROR_INVALID_INPUT = -2,
    ERROR_OUT_OF_RANGE = -3,
    ERROR_MEMORY = -4,
    ERROR_FILE = -5
} ErrorCode;

// エラーメッセージを表示する関数
void print_error(ErrorCode code) {
    switch (code) {
        case ERROR_NULL_POINTER:
            printf("エラー: NULLポインタが渡されました\n");
            break;
        case ERROR_INVALID_INPUT:
            printf("エラー: 無効な入力です\n");
            break;
        case ERROR_OUT_OF_RANGE:
            printf("エラー: 範囲外のアクセスです\n");
            break;
        case ERROR_MEMORY:
            printf("エラー: メモリ確保に失敗しました\n");
            break;
        case ERROR_FILE:
            printf("エラー: ファイル操作に失敗しました\n");
            break;
        default:
            printf("不明なエラー\n");
    }
}

/* ============================================
   例1: 配列操作のエラーハンドリング
   ============================================ */

// 配列の要素を安全に取得
ErrorCode get_array_element(int arr[], int size, int index, int* result) {
    // エラーチェック1: NULLポインタ
    if (arr == NULL || result == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    // エラーチェック2: 範囲チェック
    if (index < 0 || index >= size) {
        return ERROR_OUT_OF_RANGE;
    }
    
    // 正常処理
    *result = arr[index];
    return SUCCESS;
}

// 配列の要素を安全に設定
ErrorCode set_array_element(int arr[], int size, int index, int value) {
    if (arr == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    if (index < 0 || index >= size) {
        return ERROR_OUT_OF_RANGE;
    }
    
    arr[index] = value;
    return SUCCESS;
}

/* ============================================
   例2: 文字列操作のエラーハンドリング
   ============================================ */

// 安全な文字列コピー
ErrorCode safe_string_copy(char* dest, const char* src, int dest_size) {
    // エラーチェック1: NULLポインタ
    if (dest == NULL || src == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    // エラーチェック2: サイズチェック
    if (dest_size <= 0) {
        return ERROR_INVALID_INPUT;
    }
    
    // 安全にコピー(バッファオーバーフロー防止)
    strncpy(dest, src, dest_size - 1);
    dest[dest_size - 1] = '\0';  // 必ず終端文字を付ける
    
    return SUCCESS;
}

/* ============================================
   例3: 動的メモリのエラーハンドリング
   ============================================ */

// 安全な配列の動的確保
ErrorCode create_int_array(int** arr, int size) {
    // エラーチェック1: NULLポインタ
    if (arr == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    // エラーチェック2: サイズチェック
    if (size <= 0) {
        return ERROR_INVALID_INPUT;
    }
    
    // メモリ確保
    *arr = (int*)malloc(size * sizeof(int));
    
    // エラーチェック3: メモリ確保成功?
    if (*arr == NULL) {
        return ERROR_MEMORY;
    }
    
    // 初期化(安全のため)
    for (int i = 0; i < size; i++) {
        (*arr)[i] = 0;
    }
    
    return SUCCESS;
}

/* ============================================
   例4: ファイル操作のエラーハンドリング
   ============================================ */

// 安全なファイル読み込み
ErrorCode read_file_content(const char* filename, char* buffer, int buffer_size) {
    // エラーチェック1: NULLポインタ
    if (filename == NULL || buffer == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    // エラーチェック2: サイズチェック
    if (buffer_size <= 0) {
        return ERROR_INVALID_INPUT;
    }
    
    // ファイルを開く
    FILE* file = fopen(filename, "r");
    
    // エラーチェック3: ファイルが開けたか?
    if (file == NULL) {
        return ERROR_FILE;
    }
    
    // ファイルを読む
    if (fgets(buffer, buffer_size, file) == NULL) {
        fclose(file);
        return ERROR_FILE;
    }
    
    fclose(file);
    return SUCCESS;
}

/* ============================================
   例5: 計算のエラーハンドリング
   ============================================ */

// 安全な割り算
ErrorCode safe_divide(int a, int b, int* result) {
    if (result == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    // ゼロ除算チェック
    if (b == 0) {
        return ERROR_INVALID_INPUT;
    }
    
    *result = a / b;
    return SUCCESS;
}

// 安全な平方根(負の数チェック)
ErrorCode safe_sqrt(double value, double* result) {
    if (result == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    if (value < 0) {
        return ERROR_INVALID_INPUT;
    }
    
    // 簡易的な平方根計算(実際はmath.hのsqrt使用)
    *result = value;  // 簡略化
    return SUCCESS;
}

/* ============================================
   メイン関数: 各例のテスト
   ============================================ */

int main() {
    printf("=== エラーハンドリングの実例 ===\n\n");
    
    // 例1: 配列操作
    printf("【例1】配列操作\n");
    int arr[] = {10, 20, 30, 40, 50};
    int value;
    
    ErrorCode result = get_array_element(arr, 5, 2, &value);
    if (result == SUCCESS) {
        printf("✓ arr[2] = %d\n", value);
    } else {
        print_error(result);
    }
    
    result = get_array_element(arr, 5, 10, &value);  // 範囲外
    if (result != SUCCESS) {
        printf("✓ ");
        print_error(result);
    }
    
    // 例2: 文字列操作
    printf("\n【例2】文字列操作\n");
    char dest[10];
    result = safe_string_copy(dest, "Hello, World!", 10);
    if (result == SUCCESS) {
        printf("✓ コピー成功: %s\n", dest);
    }
    
    // 例3: 動的メモリ
    printf("\n【例3】動的メモリ確保\n");
    int* dynamic_arr = NULL;
    result = create_int_array(&dynamic_arr, 5);
    if (result == SUCCESS) {
        printf("✓ 配列確保成功\n");
        dynamic_arr[0] = 100;
        printf("✓ dynamic_arr[0] = %d\n", dynamic_arr[0]);
        free(dynamic_arr);  // 忘れずに解放
    } else {
        print_error(result);
    }
    
    // 例4: ファイル操作
    printf("\n【例4】ファイル操作\n");
    char buffer[100];
    result = read_file_content("存在しないファイル.txt", buffer, 100);
    if (result != SUCCESS) {
        printf("✓ ");
        print_error(result);
    }
    
    // 例5: 計算
    printf("\n【例5】安全な計算\n");
    int div_result;
    result = safe_divide(10, 2, &div_result);
    if (result == SUCCESS) {
        printf("✓ 10 / 2 = %d\n", div_result);
    }
    
    result = safe_divide(10, 0, &div_result);  // ゼロ除算
    if (result != SUCCESS) {
        printf("✓ ");
        print_error(result);
    }
    
    printf("\n=== すべてのテスト完了 ===\n");
    return 0;
}
