# C言語プログラム作成手順書

## 目次
1. [プログラム設計フェーズ](#1-プログラム設計フェーズ)
2. [開発環境準備](#2-開発環境準備)
3. [実装フェーズ](#3-実装フェーズ)
4. [テスト・デバッグフェーズ](#4-テストデバッグフェーズ)
5. [最適化・リファクタリング](#5-最適化リファクタリング)
6. [効率的な関数作成手順](#6-効率的な関数作成手順)
7. [チェックリスト](#7-チェックリスト)

---

## 1. プログラム設計フェーズ

### 1.1 要件定義
```
□ プログラムの目的を明確にする
□ 入力データの形式を決める
□ 出力データの形式を決める
□ 制約条件を洗い出す(メモリ、速度、環境など)
```

### 1.2 機能分解
```
□ 必要な機能をリストアップ
□ 各機能を関数単位に分割
□ 関数間の依存関係を図示
□ データ構造を設計(構造体、配列など)
```

### 1.3 ファイル構成の決定
```
小規模プログラム:
  main.c (すべてのコード)

中規模プログラム:
  main.c          (メイン処理)
  functions.c     (関数実装)
  functions.h     (関数宣言)

大規模プログラム:
  main.c
  module1.c / module1.h
  module2.c / module2.h
  utils.c / utils.h
  Makefile
```

---

## 2. 開発環境準備

### 2.1 必要なツール
```bash
# Windows環境
- コンパイラ: gcc (MinGW), MSVC, Clang
- エディタ: VS Code, Vim, Visual Studio
- デバッガ: gdb, Visual Studio Debugger
- ビルドツール: make, CMake

# 確認コマンド
gcc --version
gdb --version
```

### 2.2 プロジェクトディレクトリ作成
```bash
mkdir my_project
cd my_project
mkdir src include bin obj
```

```
プロジェクト構造例:
my_project/
  ├── src/          # ソースファイル(.c)
  ├── include/      # ヘッダファイル(.h)
  ├── bin/          # 実行ファイル
  ├── obj/          # オブジェクトファイル(.o)
  ├── Makefile
  └── README.md
```

---

## 3. 実装フェーズ

### 3.1 ヘッダファイル作成(複数ファイルの場合)

**include/functions.h**
```c
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// インクルードガード(重複防止)

// 必要なヘッダ
#include <stdio.h>
#include <stdlib.h>

// 定数定義
#define MAX_SIZE 100
#define VERSION "1.0.0"

// 型定義
typedef struct {
    int id;
    char name[50];
} User;

// 関数プロトタイプ宣言
int calculate_sum(int a, int b);
void print_array(int arr[], int size);
User* create_user(int id, const char* name);

#endif // FUNCTIONS_H
```

### 3.2 実装ファイル作成

**src/functions.c**
```c
#include "../include/functions.h"
#include <string.h>

// 関数の実装
int calculate_sum(int a, int b) {
    return a + b;
}

void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

User* create_user(int id, const char* name) {
    User* user = (User*)malloc(sizeof(User));
    if (user == NULL) {
        return NULL;
    }
    user->id = id;
    strncpy(user->name, name, sizeof(user->name) - 1);
    user->name[sizeof(user->name) - 1] = '\0';
    return user;
}
```

### 3.3 メインファイル作成

**src/main.c**
```c
#include <stdio.h>
#include "../include/functions.h"

int main(int argc, char* argv[]) {
    // 1. 初期化
    printf("Program started\n");
    
    // 2. メイン処理
    int result = calculate_sum(10, 20);
    printf("Sum: %d\n", result);
    
    int arr[] = {1, 2, 3, 4, 5};
    print_array(arr, 5);
    
    // 3. 動的メモリ使用例
    User* user = create_user(1, "Taro");
    if (user != NULL) {
        printf("User: %d, %s\n", user->id, user->name);
        free(user);  // メモリ解放
    }
    
    // 4. 終了処理
    printf("Program finished\n");
    return 0;
}
```

### 3.4 段階的実装の推奨順序

```
ステップ1: スケルトン作成
  □ main関数の基本構造
  □ 必要な関数の宣言のみ
  □ コンパイルが通ることを確認

ステップ2: コア機能実装
  □ 最も重要な関数から実装
  □ 1つ実装したらコンパイル・テスト
  □ エラーハンドリングは後回し

ステップ3: エラー処理追加
  □ NULL チェック
  □ 境界値チェック
  □ エラーメッセージ出力

ステップ4: 補助機能追加
  □ ログ出力
  □ デバッグ用print文
  □ コメント追加
```

---

## 4. テスト・デバッグフェーズ

### 4.1 コンパイル手順

```bash
# 単一ファイル
gcc -Wall -Wextra -g main.c -o program.exe

# 複数ファイル
gcc -Wall -Wextra -g src/main.c src/functions.c -I include -o bin/program.exe

# オプション説明:
# -Wall -Wextra : 警告を表示
# -g            : デバッグ情報を含める
# -I include    : ヘッダファイルの検索パス
# -o            : 出力ファイル名
```

### 4.2 Makefile作成(効率化)

**Makefile**
```makefile
CC = gcc
CFLAGS = -Wall -Wextra -g -I include
SRCDIR = src
OBJDIR = obj
BINDIR = bin

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
TARGET = $(BINDIR)/program.exe

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /Q $(OBJDIR)\*.o $(TARGET)

run: $(TARGET)
	$(TARGET)

.PHONY: all clean run
```

```bash
# 使用方法
make          # ビルド
make run      # 実行
make clean    # クリーンアップ
```

### 4.3 デバッグ手順

```bash
# gdbでデバッグ
gdb program.exe

# gdb基本コマンド
(gdb) break main          # ブレークポイント設定
(gdb) run                 # 実行開始
(gdb) next                # 次の行へ(関数に入らない)
(gdb) step                # 次の行へ(関数に入る)
(gdb) print variable      # 変数の値を表示
(gdb) continue            # 次のブレークポイントまで実行
(gdb) quit                # 終了
```

### 4.4 テストケース作成

```c
// test.c
#include <assert.h>
#include "../include/functions.h"

void test_calculate_sum() {
    assert(calculate_sum(2, 3) == 5);
    assert(calculate_sum(-1, 1) == 0);
    assert(calculate_sum(0, 0) == 0);
    printf("test_calculate_sum: PASSED\n");
}

void test_create_user() {
    User* user = create_user(1, "Test");
    assert(user != NULL);
    assert(user->id == 1);
    free(user);
    printf("test_create_user: PASSED\n");
}

int main() {
    test_calculate_sum();
    test_create_user();
    printf("All tests passed!\n");
    return 0;
}
```

---

## 5. 最適化・リファクタリング

### 5.1 コードレビューチェックリスト

```
□ メモリリークがないか(malloc/freeのペア確認)
□ 配列の境界チェックがあるか
□ NULLポインタチェックがあるか
□ マジックナンバーを定数化したか
□ 関数は1つの責務のみか(単一責任原則)
□ 関数名・変数名は分かりやすいか
□ コメントは適切か
```

### 5.2 パフォーマンス最適化

```c
// 最適化前
for (int i = 0; i < strlen(str); i++) {  // 毎回strlen()を呼ぶ
    // 処理
}

// 最適化後
int len = strlen(str);
for (int i = 0; i < len; i++) {
    // 処理
}
```

```bash
# 最適化オプション付きコンパイル
gcc -O2 -Wall main.c -o program.exe

# -O0: 最適化なし(デバッグ用)
# -O1: 基本的な最適化
# -O2: 推奨される最適化
# -O3: 積極的な最適化
```

---

## 6. 効率的な関数作成手順

### 6.1 関数設計の5ステップ

```
ステップ1: 関数の目的を1文で書く
  例: "配列の最大値を見つける"

ステップ2: 入力・出力を決める
  入力: int arr[], int size
  出力: int (最大値)

ステップ3: 関数シグネチャを書く
  int find_max(int arr[], int size);

ステップ4: エッジケースを考える
  - 配列がNULL
  - sizeが0以下
  - 負の数を含む

ステップ5: 実装する
```

### 6.2 関数作成テンプレート

```c
/**
 * @brief 関数の簡潔な説明
 * 
 * @param param1 パラメータ1の説明
 * @param param2 パラメータ2の説明
 * @return 戻り値の説明
 * 
 * @note 注意事項があれば記載
 * @example
 *   int result = my_function(10, 20);
 */
int my_function(int param1, int param2) {
    // 1. 入力検証
    if (param1 < 0 || param2 < 0) {
        fprintf(stderr, "Error: Invalid parameters\n");
        return -1;
    }
    
    // 2. メイン処理
    int result = param1 + param2;
    
    // 3. 戻り値
    return result;
}
```

### 6.3 よく使う関数パターン

**パターン1: 配列処理関数**
```c
void process_array(int arr[], int size, int (*operation)(int)) {
    for (int i = 0; i < size; i++) {
        arr[i] = operation(arr[i]);
    }
}

int double_value(int x) { return x * 2; }

// 使用例
int data[] = {1, 2, 3};
process_array(data, 3, double_value);
```

**パターン2: 構造体操作関数**
```c
// 初期化関数
void init_user(User* user, int id, const char* name) {
    if (user == NULL) return;
    user->id = id;
    strncpy(user->name, name, sizeof(user->name) - 1);
}

// 表示関数
void print_user(const User* user) {
    if (user == NULL) return;
    printf("ID: %d, Name: %s\n", user->id, user->name);
}
```

**パターン3: エラーハンドリング付き関数**
```c
typedef enum {
    SUCCESS = 0,
    ERROR_NULL_POINTER = -1,
    ERROR_INVALID_SIZE = -2,
    ERROR_MEMORY = -3
} ErrorCode;

ErrorCode safe_array_copy(int* dest, const int* src, int size) {
    if (dest == NULL || src == NULL) {
        return ERROR_NULL_POINTER;
    }
    if (size <= 0) {
        return ERROR_INVALID_SIZE;
    }
    
    for (int i = 0; i < size; i++) {
        dest[i] = src[i];
    }
    
    return SUCCESS;
}
```

---

## 7. チェックリスト

### 設計段階
- [ ] 要件を文書化した
- [ ] 必要な関数をリストアップした
- [ ] データ構造を決定した
- [ ] ファイル構成を決めた

### 実装段階
- [ ] ヘッダファイルにインクルードガードを付けた
- [ ] 関数にコメントを付けた
- [ ] マジックナンバーを定数化した
- [ ] エラーチェックを実装した

### テスト段階
- [ ] 警告なしでコンパイルできる
- [ ] 正常系のテストをした
- [ ] 異常系のテストをした
- [ ] メモリリークをチェックした

### 完成段階
- [ ] コードをフォーマットした
- [ ] 不要なコメント・デバッグコードを削除した
- [ ] README.mdを作成した
- [ ] バージョン管理(Git)にコミットした

---

## 付録: よくあるエラーと対処法

### コンパイルエラー
```
エラー: undefined reference to 'function'
対処: 関数の実装ファイルをリンクし忘れ
     gcc main.c functions.c -o program

エラー: implicit declaration of function
対処: ヘッダファイルのインクルード忘れ
     #include "functions.h" を追加
```

### 実行時エラー
```
Segmentation fault
原因: NULLポインタアクセス、配列の範囲外アクセス
対処: gdbでデバッグ、ポインタチェック追加

Memory leak
原因: malloc/freeのペアが不一致
対処: Valgrindなどのツールで検出
```

---

## 参考リソース

- C言語規格: ISO/IEC 9899
- コーディング規約: MISRA C, CERT C
- デバッグツール: gdb, Valgrind
- 静的解析: cppcheck, clang-tidy

