# C言語デバッグガイド - 完全版
## Windows + VS Code + MinGW環境

---

## 目次

1. デバッグの基本概念
2. 環境準備（VS Code + MinGW）
3. レベル1：初心者向けデバッグ手法
4. レベル2：中級者向けデバッグ手法
5. レベル3：上級者向けデバッグ手法
6. バグの種類別対処法
7. メモリリーク対策
8. デバッグのベストプラクティス

---

## 1. デバッグの基本概念

### デバッグとは
プログラムの誤り（バグ）を発見し、修正するプロセスです。

### デバッグの4つのステップ
1. **再現**: バグを確実に再現できる状態にする
2. **特定**: バグの原因箇所を特定する
3. **修正**: コードを修正する
4. **検証**: 修正が正しいことを確認する

### バグの主な種類
- **構文エラー**: コンパイル時に検出される
- **実行時エラー**: プログラム実行中にクラッシュ
- **論理エラー**: 動作するが結果が間違っている
- **メモリエラー**: メモリリーク、不正アクセス

---

## 2. 環境準備（VS Code + MinGW）

### 必要なもの
- Visual Studio Code
- MinGW（gcc コンパイラ）
- C/C++ 拡張機能（Microsoft製）

### コンパイルオプションの設定

デバッグに適したコンパイルオプション：

```bash
gcc -Wall -Wextra -g -O0 program.c -o program.exe
```

**オプションの意味：**
- `-Wall`: 基本的な警告を有効化
- `-Wextra`: 追加の警告を有効化
- `-g`: デバッグ情報を含める
- `-O0`: 最適化を無効化（デバッグしやすくする）



---

## 3. レベル1：初心者向けデバッグ手法

### 3.1 printf()デバッグ

最も基本的で効果的な手法です。

#### ステップ1：変数の値を確認
```c
int x = 10;
printf("x の値: %d\n", x);  // 変数の値を出力
```

#### ステップ2：実行フローを追跡
```c
printf("=== 関数開始 ===\n");
// 処理
printf("=== 関数終了 ===\n");
```

#### ステップ3：条件分岐の確認
```c
if (x > 0) {
    printf("DEBUG: x は正の数です\n");
} else {
    printf("DEBUG: x は0以下です\n");
}
```

#### ステップ4：ループの確認
```c
for (int i = 0; i < 5; i++) {
    printf("DEBUG: ループ %d 回目\n", i);
}
```

### 3.2 コンパイラ警告の活用

#### ステップ1：警告を有効にしてコンパイル
```bash
gcc -Wall -Wextra program.c -o program.exe
```

#### ステップ2：警告メッセージを読む
```
warning: unused variable 'x' [-Wunused-variable]
warning: format '%d' expects argument of type 'int', but argument 2 has type 'float'
```

#### ステップ3：警告を修正
すべての警告を修正することで、多くのバグを未然に防げます。

### 3.3 コメントアウトによる切り分け

#### ステップ1：問題のある部分を特定
```c
// この部分は正常に動作
function1();

// この部分でエラーが起きる？
// function2();  // コメントアウトして確認

function3();
```

#### ステップ2：段階的にコメントを外す
問題箇所を絞り込んでいきます。



---

## 4. レベル2：中級者向けデバッグ手法

### 4.1 アサーション（assert）の使用

#### ステップ1：assert.h をインクルード
```c
#include <assert.h>
```

#### ステップ2：前提条件をチェック
```c
void divide(int a, int b) {
    assert(b != 0);  // b が 0 でないことを確認
    printf("結果: %d\n", a / b);
}
```

#### ステップ3：実行時にチェック
アサーションが失敗すると、プログラムが停止し、エラー箇所を表示します。

### 4.2 VS Code デバッガの使用

#### ステップ1：launch.json の設定
VS Code で `.vscode/launch.json` を作成：

```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "C Debug",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/${fileBasenameNoExtension}.exe",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "miDebuggerPath": "C:/MinGW/bin/gdb.exe",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ],
            "preLaunchTask": "C/C++: gcc.exe build active file"
        }
    ]
}
```

#### ステップ2：ブレークポイントの設定
- コード行番号の左側をクリックして赤い点を表示
- プログラムはその行で一時停止します

#### ステップ3：デバッグ実行
- F5 キーを押してデバッグ開始
- F10: ステップオーバー（次の行へ）
- F11: ステップイン（関数内部へ）
- Shift+F11: ステップアウト（関数から出る）
- F5: 続行（次のブレークポイントまで）

#### ステップ4：変数の監視
- 左側の「変数」パネルで変数の値を確認
- 「ウォッチ」に式を追加して監視

### 4.3 条件付きログ出力

#### ステップ1：デバッグマクロの定義
```c
#define DEBUG 1

#if DEBUG
    #define DEBUG_PRINT(fmt, ...) \
        printf("DEBUG [%s:%d]: " fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#else
    #define DEBUG_PRINT(fmt, ...) // 何もしない
#endif
```

#### ステップ2：使用
```c
DEBUG_PRINT("変数 x = %d\n", x);
```

#### ステップ3：リリース時は無効化
```c
#define DEBUG 0  // デバッグ出力を無効化
```



---

## 5. レベル3：上級者向けデバッグ手法

### 5.1 静的解析（コンパイラの高度な警告）

#### ステップ1：厳格なコンパイルオプション
```bash
gcc -Wall -Wextra -Wpedantic -Werror -std=c11 program.c -o program.exe
```

**オプションの意味：**
- `-Wpedantic`: 標準規格への厳格な準拠をチェック
- `-Werror`: 警告をエラーとして扱う
- `-std=c11`: C11標準を使用

#### ステップ2：追加の警告オプション
```bash
gcc -Wall -Wextra -Wshadow -Wconversion -Wuninitialized program.c
```

- `-Wshadow`: 変数のシャドーイングを警告
- `-Wconversion`: 暗黙の型変換を警告
- `-Wuninitialized`: 初期化されていない変数を警告

### 5.2 ログファイルの活用

#### ステップ1：ログファイルへの出力
```c
FILE *logfile = fopen("debug.log", "a");
fprintf(logfile, "[%s] 変数 x = %d\n", __TIME__, x);
fclose(logfile);
```

#### ステップ2：タイムスタンプ付きログ
```c
#include <time.h>

void log_message(const char *message) {
    FILE *log = fopen("debug.log", "a");
    time_t now = time(NULL);
    fprintf(log, "[%s] %s\n", ctime(&now), message);
    fclose(log);
}
```

#### ステップ3：ログレベルの実装
```c
enum LogLevel { ERROR, WARNING, INFO, DEBUG };

void log_with_level(enum LogLevel level, const char *message) {
    const char *level_str[] = {"ERROR", "WARNING", "INFO", "DEBUG"};
    FILE *log = fopen("debug.log", "a");
    fprintf(log, "[%s] %s\n", level_str[level], message);
    fclose(log);
}
```

### 5.3 コアダンプ解析（MinGW環境）

#### ステップ1：セグメンテーションフォルトの情報取得
MinGWでは限定的ですが、エラー情報を取得できます。

#### ステップ2：スタックトレースの手動実装
```c
#include <stdio.h>
#include <stdlib.h>

void print_trace() {
    printf("=== Stack Trace ===\n");
    printf("関数呼び出しの履歴をここに記録\n");
}

void error_handler() {
    print_trace();
    exit(1);
}
```



---

## 6. バグの種類別対処法

### 6.1 ポインタ関連のバグ

#### 問題1：NULL ポインタの参照
```c
// バグのあるコード
int *ptr = NULL;
*ptr = 10;  // クラッシュ！
```

**デバッグ手順：**
1. ポインタを使用する前に NULL チェック
```c
if (ptr != NULL) {
    *ptr = 10;
} else {
    printf("ERROR: ポインタが NULL です\n");
}
```

2. アサーションで確認
```c
assert(ptr != NULL);
*ptr = 10;
```

#### 問題2：初期化されていないポインタ
```c
// バグのあるコード
int *ptr;  // 初期化されていない
*ptr = 10;  // 不正なメモリアクセス
```

**デバッグ手順：**
1. 必ず初期化する
```c
int *ptr = NULL;  // または適切なアドレスを代入
```

2. 使用前にチェック
```c
printf("DEBUG: ptr のアドレス = %p\n", (void*)ptr);
```

#### 問題3：ダングリングポインタ
```c
// バグのあるコード
int *ptr = malloc(sizeof(int));
free(ptr);
*ptr = 10;  // 解放済みメモリへのアクセス
```

**デバッグ手順：**
1. free 後に NULL を代入
```c
free(ptr);
ptr = NULL;
```

2. 使用前にチェック
```c
if (ptr != NULL) {
    *ptr = 10;
}
```

### 6.2 配列関連のバグ

#### 問題1：配列の境界外アクセス
```c
// バグのあるコード
int arr[5];
arr[5] = 10;  // インデックス 5 は範囲外（0-4が有効）
```

**デバッグ手順：**
1. インデックスの範囲を確認
```c
int index = 5;
printf("DEBUG: index = %d, 配列サイズ = %d\n", index, 5);
if (index >= 0 && index < 5) {
    arr[index] = 10;
} else {
    printf("ERROR: インデックスが範囲外です\n");
}
```

2. ループの境界を確認
```c
// 間違い
for (int i = 0; i <= 5; i++) {  // <= は間違い
    arr[i] = i;
}

// 正しい
for (int i = 0; i < 5; i++) {
    printf("DEBUG: i = %d\n", i);
    arr[i] = i;
}
```

### 6.3 ループ関連のバグ

#### 問題1：無限ループ
```c
// バグのあるコード
int i = 0;
while (i < 10) {
    printf("%d\n", i);
    // i++ を忘れている
}
```

**デバッグ手順：**
1. ループカウンタを出力
```c
int i = 0;
int count = 0;
while (i < 10) {
    printf("DEBUG: ループ %d 回目, i = %d\n", count++, i);
    if (count > 100) {
        printf("ERROR: 無限ループの可能性\n");
        break;
    }
    i++;
}
```

2. ループ条件を確認
```c
printf("DEBUG: ループ開始前 i = %d\n", i);
while (i < 10) {
    printf("DEBUG: ループ内 i = %d\n", i);
    i++;
}
printf("DEBUG: ループ終了後 i = %d\n", i);
```

### 6.4 論理エラー

#### 問題1：条件式の間違い
```c
// バグのあるコード
if (x = 10) {  // == ではなく = を使用
    printf("x は 10 です\n");
}
```

**デバッグ手順：**
1. 条件式を出力
```c
printf("DEBUG: x = %d\n", x);
if (x == 10) {
    printf("x は 10 です\n");
}
```

2. コンパイラ警告を確認
```bash
gcc -Wall program.c
# warning: suggest parentheses around assignment used as truth value
```



---

## 7. メモリリーク対策

### 7.1 メモリリークとは

メモリリークは、動的に確保したメモリを解放せずに放置する現象です。

```c
// メモリリークの例
void leak_example() {
    int *ptr = malloc(sizeof(int) * 100);
    // free(ptr) を忘れている
}  // 関数終了時、ptr は消えるがメモリは残る
```

### 7.2 メモリリークの検出手順

#### ステップ1：malloc/free のペアを確認

**チェックリスト：**
- すべての `malloc()` に対応する `free()` があるか
- すべての `calloc()` に対応する `free()` があるか
- すべての `realloc()` が適切に処理されているか

#### ステップ2：手動でメモリ使用を追跡

```c
// デバッグ用のカウンタ
static int malloc_count = 0;
static int free_count = 0;

void *debug_malloc(size_t size) {
    void *ptr = malloc(size);
    malloc_count++;
    printf("DEBUG: malloc #%d (%zu bytes) at %p\n", 
           malloc_count, size, ptr);
    return ptr;
}

void debug_free(void *ptr) {
    free_count++;
    printf("DEBUG: free #%d at %p\n", free_count, ptr);
    free(ptr);
}

// プログラム終了時にチェック
void check_memory_leaks() {
    printf("=== メモリチェック ===\n");
    printf("malloc 呼び出し: %d\n", malloc_count);
    printf("free 呼び出し: %d\n", free_count);
    if (malloc_count != free_count) {
        printf("WARNING: メモリリークの可能性があります！\n");
    }
}
```

#### ステップ3：メモリ割り当てのパターンを確認

**よくあるメモリリークのパターン：**

1. **早期リターン**
```c
void process_data() {
    int *data = malloc(sizeof(int) * 100);
    
    if (error_condition) {
        return;  // free(data) を忘れている
    }
    
    // 処理
    free(data);
}

// 修正版
void process_data_fixed() {
    int *data = malloc(sizeof(int) * 100);
    
    if (error_condition) {
        free(data);  // 追加
        return;
    }
    
    // 処理
    free(data);
}
```

2. **ループ内での割り当て**
```c
// バグのあるコード
for (int i = 0; i < 10; i++) {
    int *temp = malloc(sizeof(int));
    // free(temp) を忘れている
}

// 修正版
for (int i = 0; i < 10; i++) {
    int *temp = malloc(sizeof(int));
    // 処理
    free(temp);
}
```

3. **再割り当て**
```c
// バグのあるコード
int *ptr = malloc(sizeof(int) * 10);
ptr = malloc(sizeof(int) * 20);  // 最初のメモリが失われる

// 修正版
int *ptr = malloc(sizeof(int) * 10);
free(ptr);
ptr = malloc(sizeof(int) * 20);
```

### 7.3 メモリリーク防止のベストプラクティス

#### 実践1：所有権を明確にする
```c
// 関数がメモリを割り当てる場合、呼び出し側が解放する
int *create_array(int size) {
    return malloc(sizeof(int) * size);
}

void use_array() {
    int *arr = create_array(10);
    // 使用
    free(arr);  // 呼び出し側が解放
}
```

#### 実践2：エラーハンドリングでメモリを解放
```c
void complex_function() {
    int *ptr1 = malloc(sizeof(int) * 10);
    if (ptr1 == NULL) return;
    
    int *ptr2 = malloc(sizeof(int) * 20);
    if (ptr2 == NULL) {
        free(ptr1);  // ptr1 を解放してから終了
        return;
    }
    
    // 処理
    
    free(ptr2);
    free(ptr1);
}
```

#### 実践3：構造体のメモリ管理
```c
typedef struct {
    int *data;
    int size;
} Array;

Array *create_array(int size) {
    Array *arr = malloc(sizeof(Array));
    if (arr == NULL) return NULL;
    
    arr->data = malloc(sizeof(int) * size);
    if (arr->data == NULL) {
        free(arr);
        return NULL;
    }
    
    arr->size = size;
    return arr;
}

void destroy_array(Array *arr) {
    if (arr != NULL) {
        free(arr->data);  // 内部のメモリを先に解放
        free(arr);        // 構造体自体を解放
    }
}
```



---

## 8. デバッグのベストプラクティス

### 8.1 予防的デバッグ

#### 実践1：コーディング規約を守る
- 一貫したインデント（スペース4つまたはタブ）
- 意味のある変数名を使用
- 関数は1つの機能に集中
- コメントで意図を説明

#### 実践2：小さく書いて頻繁にテスト
```c
// 悪い例：一度に大量のコードを書く
void complex_function() {
    // 100行のコード
    // テストせずに次の機能を追加
}

// 良い例：段階的に実装してテスト
void step1() {
    // 10行のコード
    // テスト
}

void step2() {
    step1();
    // 追加の10行
    // テスト
}
```

#### 実践3：入力値の検証
```c
int divide(int a, int b) {
    // 入力値を検証
    if (b == 0) {
        printf("ERROR: ゼロ除算\n");
        return 0;
    }
    return a / b;
}

void process_array(int *arr, int size) {
    // 入力値を検証
    if (arr == NULL) {
        printf("ERROR: 配列が NULL です\n");
        return;
    }
    if (size <= 0) {
        printf("ERROR: サイズが不正です\n");
        return;
    }
    // 処理
}
```

### 8.2 効率的なデバッグ戦略

#### 戦略1：二分探索法
問題のある範囲を半分ずつ絞り込む

```
1. プログラムの中間地点にprintf()を追加
2. 問題が前半か後半かを判断
3. 問題のある半分をさらに二分割
4. 繰り返す
```

#### 戦略2：最小再現コードの作成
```c
// 大きなプログラムから問題部分だけを抽出
int main() {
    // 問題を再現する最小限のコード
    int *ptr = NULL;
    *ptr = 10;  // ここでクラッシュ
    return 0;
}
```

#### 戦略3：仮説検証法
1. バグの原因について仮説を立てる
2. 仮説を検証する実験を行う
3. 結果に基づいて仮説を修正
4. 繰り返す

### 8.3 デバッグツールの使い分け

| 状況 | 推奨ツール | 理由 |
|------|-----------|------|
| 簡単な変数確認 | printf() | 最も手軽で効果的 |
| 複雑な実行フロー | VS Code デバッガ | ステップ実行で追跡 |
| メモリリーク | 手動追跡 | MinGWでは高度なツールが限定的 |
| コンパイルエラー | コンパイラ警告 | 早期発見が可能 |
| 論理エラー | assert() | 前提条件の確認 |

### 8.4 デバッグ時の心構え

#### 心構え1：焦らない
- バグは必ず原因がある
- 落ち着いて一つずつ確認

#### 心構え2：仮定を疑う
- 「このコードは正しいはず」という思い込みを捨てる
- すべてを検証する

#### 心構え3：記録を残す
- 試したことをメモする
- 同じ間違いを繰り返さない

#### 心構え4：休憩を取る
- 長時間デバッグしても進まない場合は休憩
- 新鮮な視点で見直す

### 8.5 よくあるデバッグの落とし穴

#### 落とし穴1：症状だけを修正
```c
// 悪い例：クラッシュを回避するだけ
if (ptr != NULL) {
    *ptr = 10;
}
// なぜ ptr が NULL なのか原因を調べていない

// 良い例：根本原因を調査
printf("DEBUG: ptr が NULL になった理由を調査\n");
// 初期化忘れ、メモリ割り当て失敗など
```

#### 落とし穴2：複数の変更を同時に行う
```c
// 悪い例：一度に複数箇所を変更
// 変更1
// 変更2
// 変更3
// どの変更が効果的だったか不明

// 良い例：一つずつ変更してテスト
// 変更1 → テスト
// 変更2 → テスト
// 変更3 → テスト
```

#### 落とし穴3：デバッグコードを残す
```c
// 悪い例：デバッグ用のprintfが残っている
printf("DEBUG: x = %d\n", x);  // 本番環境で実行される

// 良い例：条件付きコンパイル
#ifdef DEBUG
    printf("DEBUG: x = %d\n", x);
#endif
```



---

## 9. 実践的なデバッグ演習

### 演習1：セグメンテーションフォルトの修正

**問題のあるコード：**
```c
#include <stdio.h>

int main() {
    int *ptr;
    *ptr = 100;
    printf("%d\n", *ptr);
    return 0;
}
```

**デバッグ手順：**
1. コンパイルして実行
2. クラッシュを確認
3. printf()でポインタの値を確認
4. 初期化されていないことを発見
5. 修正

**修正版：**
```c
#include <stdio.h>

int main() {
    int value;
    int *ptr = &value;  // 修正：適切に初期化
    *ptr = 100;
    printf("%d\n", *ptr);
    return 0;
}
```

### 演習2：配列の境界外アクセス

**問題のあるコード：**
```c
#include <stdio.h>

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    for (int i = 0; i <= 5; i++) {
        printf("%d\n", arr[i]);
    }
    return 0;
}
```

**デバッグ手順：**
1. ループの範囲を確認
2. printf()でインデックスを出力
3. i = 5 が範囲外であることを発見
4. 修正

**修正版：**
```c
#include <stdio.h>

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++) {  // 修正：< に変更
        printf("arr[%d] = %d\n", i, arr[i]);
    }
    return 0;
}
```

### 演習3：メモリリーク

**問題のあるコード：**
```c
#include <stdio.h>
#include <stdlib.h>

void create_data() {
    int *data = malloc(sizeof(int) * 100);
    // free(data) を忘れている
}

int main() {
    for (int i = 0; i < 10; i++) {
        create_data();
    }
    return 0;
}
```

**デバッグ手順：**
1. malloc/free のペアを確認
2. free() が呼ばれていないことを発見
3. 修正

**修正版：**
```c
#include <stdio.h>
#include <stdlib.h>

void create_data() {
    int *data = malloc(sizeof(int) * 100);
    if (data == NULL) {
        printf("ERROR: メモリ割り当て失敗\n");
        return;
    }
    // データ処理
    free(data);  // 修正：メモリを解放
}

int main() {
    for (int i = 0; i < 10; i++) {
        create_data();
    }
    return 0;
}
```

---

## 10. チェックリスト

### コンパイル前のチェック
- [ ] すべての変数が初期化されているか
- [ ] すべてのポインタが NULL チェックされているか
- [ ] 配列のインデックスが範囲内か
- [ ] ループの終了条件が正しいか
- [ ] malloc/free のペアが揃っているか

### コンパイル時のチェック
- [ ] `-Wall -Wextra` オプションを使用しているか
- [ ] すべての警告を確認したか
- [ ] 警告を修正したか

### 実行時のチェック
- [ ] 期待通りの出力が得られるか
- [ ] エッジケース（境界値）でテストしたか
- [ ] 異常な入力でテストしたか
- [ ] メモリリークがないか

### デバッグ時のチェック
- [ ] 問題を再現できるか
- [ ] 最小再現コードを作成したか
- [ ] 仮説を立てたか
- [ ] 一つずつ変更してテストしているか

---

## 11. まとめ

### デバッグの基本原則
1. **予防が最善**: 最初から良いコードを書く
2. **小さく始める**: 段階的に実装してテスト
3. **記録を残す**: 試したことをメモする
4. **焦らない**: 落ち着いて一つずつ確認

### レベル別推奨手法
- **初心者**: printf()デバッグ、コンパイラ警告
- **中級者**: VS Code デバッガ、assert()
- **上級者**: ログファイル、静的解析

### 重要なポイント
- すべてのポインタを初期化する
- 配列の境界を確認する
- malloc/free のペアを確認する
- コンパイラ警告を無視しない
- 小さく書いて頻繁にテストする

---

## 参考資料

### VS Code 設定ファイル
- `.vscode/launch.json`: デバッグ設定
- `.vscode/tasks.json`: ビルドタスク設定

### 推奨コンパイルコマンド
```bash
# 開発時
gcc -Wall -Wextra -g -O0 program.c -o program.exe

# リリース時
gcc -Wall -Wextra -O2 program.c -o program.exe
```

### 便利なマクロ
```c
#define DEBUG_PRINT(fmt, ...) \
    printf("DEBUG [%s:%d]: " fmt, __FILE__, __LINE__, ##__VA_ARGS__)

#define ASSERT_NOT_NULL(ptr) \
    if ((ptr) == NULL) { \
        printf("ERROR: %s is NULL at %s:%d\n", #ptr, __FILE__, __LINE__); \
        exit(1); \
    }
```

---

このガイドを活用して、効率的なデバッグスキルを身につけてください！
