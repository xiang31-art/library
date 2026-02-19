# コアダンプの活用ガイド（Linux環境）

## コアダンプとは

コアダンプ（core dump）は、プログラムがクラッシュした瞬間のメモリの状態を保存したファイルです。

### コアダンプに含まれる情報
- プログラムのメモリ内容
- レジスタの値
- スタックの状態
- 実行中だった命令のアドレス
- すべての変数の値

### なぜ重要か
- クラッシュ時の正確な状態を後から解析できる
- 再現が難しいバグの調査に有効
- 本番環境でのクラッシュ原因を特定できる

---

## 1. コアダンプの有効化

### ステップ1：コアダンプサイズの制限を確認

```bash
# 現在の設定を確認
ulimit -c
# 0 と表示される場合、コアダンプは無効
```

### ステップ2：コアダンプを有効化

```bash
# 無制限にコアダンプを生成
ulimit -c unlimited

# 特定のサイズまで許可（例：100MB）
ulimit -c 102400
```

### ステップ3：永続的に有効化

`~/.bashrc` または `~/.bash_profile` に追加：

```bash
# コアダンプを有効化
ulimit -c unlimited
```

### ステップ4：コアダンプの保存場所を確認

```bash
# コアダンプのパターンを確認
cat /proc/sys/kernel/core_pattern

# 一般的な設定例
# core                    # カレントディレクトリに "core" として保存
# core.%p                 # "core.プロセスID" として保存
# /var/crash/core.%p.%e   # 特定のディレクトリに保存
```

---

## 2. コアダンプの生成

### テストプログラムの作成

```c
// crash_test.c
#include <stdio.h>
#include <stdlib.h>

void function_c() {
    int *ptr = NULL;
    printf("NULL ポインタにアクセスします...\n");
    *ptr = 42;  // ここでクラッシュ
}

void function_b() {
    int local_b = 200;
    printf("function_b: local_b = %d\n", local_b);
    function_c();
}

void function_a() {
    int local_a = 100;
    printf("function_a: local_a = %d\n", local_a);
    function_b();
}

int main() {
    int main_var = 10;
    printf("main: main_var = %d\n", main_var);
    function_a();
    return 0;
}
```

### コンパイルと実行

```bash
# デバッグ情報付きでコンパイル（重要！）
gcc -g -Wall crash_test.c -o crash_test

# 実行
./crash_test

# 出力例
# main: main_var = 10
# function_a: local_a = 100
# function_b: local_b = 200
# NULL ポインタにアクセスします...
# Segmentation fault (core dumped)

# コアダンプファイルが生成される
ls -lh core*
# -rw------- 1 user user 352K Jan 1 12:00 core
```

---

## 3. gdb でコアダンプを解析

### 基本的な解析手順

#### ステップ1：gdb でコアダンプを開く

```bash
gdb ./crash_test core
```

または

```bash
gdb ./crash_test -c core
```

#### ステップ2：クラッシュ箇所を確認

```gdb
# gdb プロンプトで
(gdb) where
# または
(gdb) backtrace
# または短縮形
(gdb) bt

# 出力例
#0  0x00005555555551a9 in function_c () at crash_test.c:8
#1  0x00005555555551d5 in function_b () at crash_test.c:14
#2  0x0000555555555201 in function_a () at crash_test.c:20
#3  0x000055555555522d in main () at crash_test.c:26
```

**解釈：**
- `#0`: クラッシュした場所（function_c の8行目）
- `#1-3`: 関数呼び出しの履歴（スタックトレース）

#### ステップ3：各フレームの詳細を確認

```gdb
# フレーム0（クラッシュ箇所）の詳細
(gdb) frame 0
(gdb) list

# 出力例
3       void function_c() {
4           int *ptr = NULL;
5           printf("NULL ポインタにアクセスします...\n");
6           *ptr = 42;  // ← ここでクラッシュ
7       }
```

#### ステップ4：変数の値を確認

```gdb
# 現在のフレームの変数
(gdb) info locals
# ptr = 0x0

# 特定の変数を表示
(gdb) print ptr
# $1 = (int *) 0x0

# ポインタが指す値を表示（可能な場合）
(gdb) print *ptr
# Cannot access memory at address 0x0
```

#### ステップ5：他のフレームの変数を確認

```gdb
# フレーム1（function_b）に移動
(gdb) frame 1
(gdb) info locals
# local_b = 200

# フレーム2（function_a）に移動
(gdb) frame 2
(gdb) info locals
# local_a = 100

# フレーム3（main）に移動
(gdb) frame 3
(gdb) info locals
# main_var = 10
```

---

## 4. 高度な解析テクニック

### 4.1 メモリの内容を確認

```gdb
# 変数のアドレスを確認
(gdb) print &main_var
# $2 = (int *) 0x7fffffffdc9c

# メモリの内容を表示（16進数）
(gdb) x/4xw 0x7fffffffdc9c
# 0x7fffffffdc9c: 0x0000000a 0x00000000 0xf7df2d90 0x00007fff

# メモリの内容を表示（10進数）
(gdb) x/4dw 0x7fffffffdc9c
# 0x7fffffffdc9c: 10      0       -136184432      32767
```

**フォーマット指定：**
- `x`: 16進数
- `d`: 10進数
- `s`: 文字列
- `w`: ワード（4バイト）
- `b`: バイト（1バイト）

### 4.2 スタックの内容を確認

```gdb
# スタックフレームの情報
(gdb) info frame

# 出力例
Stack level 0, frame at 0x7fffffffdc80:
 rip = 0x5555555551a9 in function_c (crash_test.c:8)
 called by frame at 0x7fffffffdca0
 source language c.
 Arglist at 0x7fffffffdc70, args: 
 Locals at 0x7fffffffdc70, Previous frame's sp is 0x7fffffffdc80
```

### 4.3 レジスタの値を確認

```gdb
# すべてのレジスタを表示
(gdb) info registers

# 特定のレジスタを表示
(gdb) print $rip    # 命令ポインタ
(gdb) print $rsp    # スタックポインタ
(gdb) print $rbp    # ベースポインタ
```

### 4.4 構造体の内容を確認

```c
// struct_crash.c
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    float score;
} Student;

int main() {
    Student *student = malloc(sizeof(Student));
    student->id = 12345;
    student->score = 95.5f;
    
    // 意図的にクラッシュ
    int *ptr = NULL;
    *ptr = 10;
    
    return 0;
}
```

```gdb
# gdb で解析
(gdb) frame 0
(gdb) print student
# $1 = (Student *) 0x555555559260

(gdb) print *student
# $2 = {id = 12345, name = "", score = 95.5}

# 構造体のメンバーを個別に表示
(gdb) print student->id
# $3 = 12345

(gdb) print student->score
# $4 = 95.5
```

---

## 5. 実践的な使用例

### 例1：配列の境界外アクセス

```c
// array_crash.c
#include <stdio.h>

int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    int index = 1000000;
    
    printf("arr[%d] にアクセスします\n", index);
    arr[index] = 99;  // クラッシュ
    
    return 0;
}
```

**gdb での解析：**

```gdb
(gdb) bt
#0  main () at array_crash.c:8

(gdb) print index
$1 = 1000000

(gdb) print arr
$2 = {10, 20, 30, 40, 50}

# 問題を特定：index が配列サイズを超えている
```

### 例2：ダングリングポインタ

```c
// dangling_crash.c
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr = malloc(sizeof(int) * 10);
    *ptr = 42;
    
    printf("ptr の値: %d\n", *ptr);
    free(ptr);
    
    printf("解放後にアクセス\n");
    *ptr = 100;  // クラッシュ（または不正な動作）
    
    return 0;
}
```

**gdb での解析：**

```gdb
(gdb) bt
#0  main () at dangling_crash.c:12

(gdb) print ptr
$1 = (int *) 0x555555559260

# メモリの内容を確認
(gdb) x/4xw ptr
# 解放済みメモリの内容が表示される

# 問題を特定：free 後にポインタを使用している
```

---

## 6. コアダンプのベストプラクティス

### 実践1：デバッグ情報を含めてコンパイル

```bash
# 必須
gcc -g program.c -o program

# より詳細な情報
gcc -g3 -O0 program.c -o program
```

**オプションの意味：**
- `-g`: デバッグ情報を含める
- `-g3`: 最大レベルのデバッグ情報（マクロ定義も含む）
- `-O0`: 最適化を無効化（デバッグしやすくする）

### 実践2：本番環境でのコアダンプ管理

```bash
# コアダンプを特定のディレクトリに保存
sudo sysctl -w kernel.core_pattern=/var/crash/core.%e.%p.%t

# %e: 実行ファイル名
# %p: プロセスID
# %t: タイムスタンプ
```

### 実践3：コアダンプのサイズを制限

```bash
# 最大100MBまで
ulimit -c 102400

# システム全体で設定
# /etc/security/limits.conf に追加
* soft core 102400
* hard core 102400
```

### 実践4：自動解析スクリプト

```bash
#!/bin/bash
# analyze_core.sh

PROGRAM=$1
CORE=$2

if [ ! -f "$PROGRAM" ] || [ ! -f "$CORE" ]; then
    echo "使用方法: $0 <program> <core>"
    exit 1
fi

echo "=== コアダンプ解析 ==="
echo "プログラム: $PROGRAM"
echo "コアファイル: $CORE"
echo ""

gdb -batch -ex "bt" -ex "info locals" -ex "quit" "$PROGRAM" "$CORE"
```

使用方法：
```bash
chmod +x analyze_core.sh
./analyze_core.sh crash_test core
```

---

## 7. トラブルシューティング

### 問題1：コアダンプが生成されない

**原因と対処：**

1. **ulimit が 0 に設定されている**
```bash
ulimit -c unlimited
```

2. **ディスク容量不足**
```bash
df -h
```

3. **権限の問題**
```bash
# 書き込み権限を確認
ls -ld .
```

4. **systemd がコアダンプを管理している**
```bash
# systemd のコアダンプを確認
coredumpctl list

# 特定のコアダンプを取得
coredumpctl dump <PID> > core
```

### 問題2：gdb でシンボルが見つからない

**原因：** デバッグ情報なしでコンパイルされている

**対処：**
```bash
# -g オプションを付けて再コンパイル
gcc -g program.c -o program
```

### 問題3：コアダンプが大きすぎる

**対処：**
```bash
# サイズを制限
ulimit -c 10240  # 10MB

# または、必要な情報だけを抽出
gdb -batch -ex "bt" -ex "quit" program core > backtrace.txt
```

---

## 8. まとめ

### コアダンプの活用フロー

1. **有効化**: `ulimit -c unlimited`
2. **コンパイル**: `gcc -g program.c -o program`
3. **実行**: プログラムがクラッシュしてコアダンプ生成
4. **解析**: `gdb program core`
5. **調査**: `bt`, `info locals`, `print` コマンド
6. **修正**: 原因を特定してコードを修正

### 重要なgdbコマンド

| コマンド | 説明 |
|---------|------|
| `bt` | スタックトレース表示 |
| `frame N` | フレームN に移動 |
| `info locals` | ローカル変数表示 |
| `print 変数` | 変数の値を表示 |
| `list` | ソースコード表示 |
| `x/アドレス` | メモリ内容表示 |
| `info registers` | レジスタ表示 |

### コアダンプが特に有効な場面

- 本番環境でのクラッシュ調査
- 再現が難しいバグの解析
- マルチスレッドプログラムのデッドロック調査
- メモリ破壊の原因特定

### 注意点

- コアダンプには機密情報が含まれる可能性がある
- ディスク容量を消費する
- 本番環境では適切なサイズ制限を設定する
- 定期的に古いコアダンプを削除する
