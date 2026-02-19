#include <stdio.h>
#include <string.h>

// ========================================
// 課題1: 学生の情報を管理する構造体を定義
// ========================================
// ヒント: 名前(char配列)、年齢(int)、点数(int)を持つ構造体
// ここに構造体を定義してください
struct Student {
    char name[50];
    int age;
    int score;
};


// ========================================
// 課題2: 座標を表す構造体を定義
// ========================================
// ヒント: x座標(int)とy座標(int)を持つ構造体
// ここに構造体を定義してください
struct Point {
    int x;
    int y;
};


// 関数プロトタイプ
void printStudent(struct Student s);
void updateScore(struct Student *s, int newScore);
double calculateDistance(struct Point p1, struct Point p2);
void movePoint(struct Point *p, int dx, int dy);

int main() {
    printf("=== 構造体練習問題（穴埋め形式） ===\n\n");
    
    // ========================================
    // 課題3: 構造体変数の宣言と初期化
    // ========================================
    printf("課題3: 構造体変数の宣言と初期化\n");
    
    // ヒント: struct Student型の変数student1を宣言し、
    // 名前を"田中", 年齢を20, 点数を85で初期化
    // ここにコードを書いてください
    struct Student student1 = {"田中", 20, 85};
    
    
    
    printf("学生情報: ");
    printStudent(student1);
    printf("\n");
    
    // ========================================
    // 課題4: 構造体のメンバにアクセス
    // ========================================
    printf("課題4: 構造体のメンバにアクセス\n");
    
    // ヒント: student1の点数を90に変更してください
    // ここにコードを書いてください
    student1.score = 90;
    
    printf("点数変更後: ");
    printStudent(student1);
    printf("\n");
    
    // ========================================
    // 課題5: ポインタを使って構造体を操作
    // ========================================
    printf("課題5: ポインタを使って構造体を操作\n");
    struct Student student2 = {"佐藤", 22, 75};
    printf("変更前: ");
    printStudent(student2);
    
    // updateScore関数を呼び出して点数を95に変更
    // ヒント: student2のアドレスを渡す
    // ここにコードを書いてください
    updateScore(&student2, 95);
    
    printf("変更後: ");
    printStudent(student2);
    printf("\n");
    
    // ========================================
    // 課題6: 座標構造体の操作
    // ========================================
    printf("課題6: 座標構造体の操作\n");
    
    // ヒント: Point型の変数p1を(3, 4)で初期化
    // ここにコードを書いてください
    struct Point p1 = {3, 4};
    
    printf("座標p1: (%d, %d)\n", p1.x, p1.y);
    
    // p1を(2, 3)だけ移動させる
    // ヒント: movePoint関数を使用
    // ここにコードを書いてください
    movePoint(&p1, 2, 3);
    
    printf("移動後: (%d, %d)\n", p1.x, p1.y);
    
    return 0;
}

// ========================================
// ここから下の関数を完成させてください
// ========================================

// 学生情報を表示する関数
void printStudent(struct Student s) {
    // ヒント: s.name, s.age, s.scoreを表示
    // ここにプログラムを書いてください
    printf("%s (年齢: %d, 点数: %d)\n", s.name, s.age, s.score);
}

// ポインタを使って点数を更新する関数
void updateScore(struct Student *s, int newScore) {
    // ヒント: アロー演算子(->)を使って s->score を更新
    // または (*s).score でもOK
    // ここにプログラムを書いてください
    s->score = newScore;
}

// 座標を移動させる関数
void movePoint(struct Point *p, int dx, int dy) {
    // ヒント: p->x に dx を加算、p->y に dy を加算
    // ここにプログラムを書いてください
    p->x += dx;
    p->y += dy;
}


/*
========================================
構造体のポイント:
========================================
1. 構造体の定義:
   struct 構造体名 {
       データ型 メンバ名1;
       データ型 メンバ名2;
   };

2. 構造体変数の宣言:
   struct 構造体名 変数名;

3. メンバへのアクセス:
   変数名.メンバ名

4. ポインタ経由のアクセス:
   ポインタ->メンバ名
   または (*ポインタ).メンバ名

5. 初期化:
   struct 構造体名 変数名 = {値1, 値2, ...};

========================================
解答例:
========================================

// 課題1: Student構造体の定義
struct Student {
    char name[50];
    int age;
    int score;
};

// 課題2: Point構造体の定義
struct Point {
    int x;
    int y;
};

// 課題3: 構造体変数の宣言と初期化
struct Student student1 = {"田中", 20, 85};

// 課題4: メンバへのアクセス
student1.score = 90;

// 課題5: ポインタを使った操作
updateScore(&student2, 95);

// 課題6: 座標構造体の操作
struct Point p1 = {3, 4};
movePoint(&p1, 2, 3);

// printStudent関数
void printStudent(struct Student s) {
    printf("%s (年齢: %d, 点数: %d)\n", s.name, s.age, s.score);
}

// updateScore関数
void updateScore(struct Student *s, int newScore) {
    s->score = newScore;
    // または: (*s).score = newScore;
}

// movePoint関数
void movePoint(struct Point *p, int dx, int dy) {
    p->x += dx;
    p->y += dy;
    // または:
    // (*p).x += dx;
    // (*p).y += dy;
}

========================================
補足説明:
========================================
- アロー演算子(->)は、ポインタ経由でメンバにアクセスする便利な記法
- p->x は (*p).x と同じ意味
- 構造体を関数に渡すとき:
  * 値渡し: 構造体のコピーが渡される（変更は元に影響しない）
  * ポインタ渡し: 元の構造体を直接操作できる
*/
