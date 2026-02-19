# MinGW でのセグメンテーションフォルトとエラー情報

## 重要な違い：MinGW vs Linux

### Linux環境
- ✓ "Segmentation Fault" というエラーメッセージ
- ✓ コアダンプファイルの生成
- ✓ 詳細なスタックトレース
- ✓ gdb で詳細なデバッグ情報

### MinGW（Windows）環境
- ✗ "Segmentation Fault" という用語は使われない
- ✗ コアダンプは生成されない
- ✗ 詳細なエラー情報は限定的
- ○ Windowsの「アクセス違反」として表示
- ○ 基本的なシグナルハンドリングは可能

---

## MinGW でのエラー表示

### 典型的なエラーメッセージ

```
# NULL ポインタアクセスの場合
Process finished with exit code -1073741819 (0xC0000005)
```

**エラーコードの意味：**
- `0xC0000005`: アクセス違反（ACCESS_VIOLATION）
- `0xC0000374`: ヒープ破損
- `0xC00000FD`: スタックオーバーフロー

---

## MinGW でできること

### 1. シグナルハンドリング（限定的）

```c
#include <signal.h>

void signal_handler(int sig) {
    if (sig == SIGSEGV) {
        printf("不正なメモリアクセスが発生しました\n");
        exit(1);
    }
}

int main() {
    signal(SIGSEGV, signal_handler);
    // プログラム実行
}
```

**注意：** Windows では SIGSEGV が正しく捕捉されない場合があります。

### 2. 構造化例外処理（SEH）

Windows 固有の機能を使用：

```c
#include <windows.h>
#include <excpt.h>

int filter(unsigned int code, struct _EXCEPTION_POINTERS *ep) {
    printf("例外コード: 0x%X\n", code);
    
    if (code == EXCEPTION_ACCESS_VIOLATION) {
        printf("アクセス違反が発生しました\n");
        printf("アドレス: %p\n", ep->ExceptionRecord->ExceptionAddress);
        return EXCEPTION_EXECUTE_HANDLER;
    }
    
    return EXCEPTION_CONTINUE_SEARCH;
}

int main() {
    __try {
        int *ptr = NULL;
        *ptr = 10;  // アクセス違反
    }
    __except(filter(GetExceptionCode(), GetExceptionInformation())) {
        printf("例外を処理しました\n");
    }
    
    return 0;
}
```

### 3. デバッグ情報の出力

```c
#include <stdio.h>

void debug_pointer(const char *name, void *ptr) {
    printf("DEBUG: %s = %p", name, ptr);
    
    if (ptr == NULL) {
        printf(" (NULL)");
    }
    
    printf("\n");
}

int main() {
    int *ptr = NULL;
    debug_pointer("ptr", ptr);
    
    if (ptr != NULL) {
        *ptr = 10;
    } else {
        printf("ERROR: ポインタが NULL です\n");
    }
    
    return 0;
}
```

---

## MinGW でのデバッグ方法

### 方法1：VS Code デバッガを使用

**手順：**
1. `-g` オプションでコンパイル
```bash
gcc -g -Wall program.c -o program.exe
```

2. VS Code でブレークポイントを設定

3. F5 でデバッグ実行

4. クラッシュ時に変数の値を確認

### 方法2：gdb を使用（コマンドライン）

```bash
# デバッグ情報付きでコンパイル
gcc -g program.c -o program.exe

# gdb で実行
gdb program.exe

# gdb コマンド
(gdb) run                    # プログラム実行
(gdb) backtrace              # スタックトレース表示
(gdb) print variable_name    # 変数の値を表示
(gdb) info locals            # ローカル変数を表示
```

### 方法3：printf() デバッグ

最も確実で効果的：

```c
#include <stdio.h>

int main() {
    printf("=== プログラム開始 ===\n");
    
    int *ptr = NULL;
    printf("DEBUG: ptr = %p\n", (void*)ptr);
    
    if (ptr == NULL) {
        printf("ERROR: ptr が NULL です\n");
        return 1;
    }
    
    printf("DEBUG: ptr に値を書き込みます\n");
    *ptr = 10;
    
    printf("=== プログラム終了 ===\n");
    return 0;
}
```

---

## 実践的なエラー検出方法

### 1. 事前チェックを徹底

```c
// ポインタの NULL チェック
if (ptr == NULL) {
    fprintf(stderr, "ERROR: ポインタが NULL です\n");
    return -1;
}

// 配列の境界チェック
if (index < 0 || index >= array_size) {
    fprintf(stderr, "ERROR: インデックスが範囲外です\n");
    return -1;
}

// メモリ割り当ての確認
ptr = malloc(size);
if (ptr == NULL) {
    fprintf(stderr, "ERROR: メモリ割り当て失敗\n");
    return -1;
}
```

### 2. アサーションを使用

```c
#include <assert.h>

void process_data(int *data, int size) {
    assert(data != NULL);
    assert(size > 0);
    
    // 処理
}
```

### 3. デバッグマクロを作成

```c
#define CHECK_NULL(ptr) \
    do { \
        if ((ptr) == NULL) { \
            fprintf(stderr, "ERROR: %s is NULL at %s:%d\n", \
                    #ptr, __FILE__, __LINE__); \
            exit(1); \
        } \
    } while(0)

int main() {
    int *ptr = NULL;
    CHECK_NULL(ptr);  // ここでエラーメッセージを出力して終了
    *ptr = 10;
    return 0;
}
```

---

## MinGW の制限を補う方法

### 1. WSL（Windows Subsystem for Linux）を使用

**利点：**
- Linux環境のツールが使える
- valgrind でメモリエラー検出
- 詳細なコアダンプ
- 完全な gdb 機能

**使用方法：**
```bash
# WSL 内で
gcc -g program.c -o program
./program

# セグメンテーションフォルトが発生
# Segmentation fault (core dumped)

# gdb で解析
gdb program core
```

### 2. AddressSanitizer を使用

MinGW でも使用可能（バージョンによる）：

```bash
gcc -fsanitize=address -g program.c -o program.exe
```

**検出できるエラー：**
- バッファオーバーフロー
- Use-after-free
- メモリリーク
- 二重解放

### 3. Dr. Memory（Windows用ツール）

無料のメモリデバッグツール：

```bash
# Dr. Memory をインストール後
drmemory.exe -- program.exe
```

---

## まとめ

### MinGW でできること
- ✓ 基本的なシグナルハンドリング
- ✓ VS Code デバッガでのステップ実行
- ✓ gdb でのデバッグ
- ✓ printf() デバッグ
- ✓ 事前チェックによる予防

### MinGW でできないこと
- ✗ Linux のようなコアダンプ
- ✗ 詳細なスタックトレース（自動）
- ✗ valgrind の使用

### 推奨アプローチ
1. **予防が最善**: NULL チェック、境界チェックを徹底
2. **VS Code デバッガ**: 視覚的にデバッグ
3. **printf() デバッグ**: 最も確実
4. **必要に応じて WSL**: 高度なツールが必要な場合

### エラー情報の取得優先順位
1. VS Code デバッガ（最も使いやすい）
2. printf() デバッグ（最も確実）
3. gdb コマンドライン（詳細な情報）
4. 構造化例外処理（Windows 固有）
5. WSL に移行（Linux ツールが必要な場合）
