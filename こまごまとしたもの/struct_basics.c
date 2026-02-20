#include <stdio.h>
#include <string.h>

/*
========================================
構造体（struct）とは？
========================================
構造体は、異なる型のデータをまとめて1つの型として扱う機能です。

例えば、学生の情報を管理する場合：
- 名前（文字列）
- 年齢（整数）
- 点数（整数）
これらをバラバラに管理するのではなく、1つにまとめられます。
*/

// ========================================
// 1. 構造体の定義
// ========================================
struct Student {
    char name[50];  // 名前
    int age;        // 年齢
    int score;      // 点数
};
// セミコロン(;)を忘れずに！

// 別の例：座標を表す構造体
struct Point {
    int x;
    int y;
};

// ========================================
// 2. 構造体変数の宣言と初期化
// ========================================
void example1_declaration() {
    printf("=== 例1: 構造体変数の宣言と初期化 ===\n");
    
    // 方法1: 宣言してから値を代入
    struct Student student1;
    strcpy(student1.name, "田中");
    student1.age = 20;
    student1.score = 85;
    
    // 方法2: 宣言と同時に初期化（おすすめ）
    struct Student student2 = {"佐藤", 22, 90};
    
    // 方法3: メンバ名を指定して初期化
    struct Student student3 = {
        .name = "鈴木",
        .age = 21,
        .score = 78
    };
    
    printf("student1: %s, %d歳, %d点\n", student1.name, student1.age, student1.score);
    printf("student2: %s, %d歳, %d点\n", student2.name, student2.age, student2.score);
    printf("student3: %s, %d歳, %d点\n\n", student3.name, student3.age, student3.score);
}

// ========================================
// 3. メンバへのアクセス（ドット演算子）
// ========================================
void example2_access() {
    printf("=== 例2: メンバへのアクセス ===\n");
    
    struct Point p1 = {10, 20};
    
    // ドット演算子(.)でメンバにアクセス
    printf("座標: (%d, %d)\n", p1.x, p1.y);
    
    // メンバの値を変更
    p1.x = 30;
    p1.y = 40;
    printf("変更後: (%d, %d)\n\n", p1.x, p1.y);
}

// ========================================
// 4. 構造体と関数（値渡し）
// ========================================
void printStudent(struct Student s) {
    // 構造体のコピーが渡される
    printf("%s (年齢: %d, 点数: %d)\n", s.name, s.age, s.score);
}

void example3_function_value() {
    printf("=== 例3: 構造体を関数に渡す（値渡し） ===\n");
    
    struct Student student = {"山田", 19, 88};
    printStudent(student);
    
    // 注意: 値渡しなので、関数内で変更しても元の変数は変わらない
    printf("\n");
}

// ========================================
// 5. 構造体とポインタ（参照渡し）
// ========================================
void updateScore(struct Student *s, int newScore) {
    // アロー演算子(->)でポインタ経由のメンバにアクセス
    s->score = newScore;
    
    // 上記は以下と同じ意味
    // (*s).score = newScore;
}

void example4_pointer() {
    printf("=== 例4: 構造体とポインタ ===\n");
    
    struct Student student = {"高橋", 23, 70};
    printf("変更前: ");
    printStudent(student);
    
    // ポインタを使って関数に渡す
    updateScore(&student, 95);
    
    printf("変更後: ");
    printStudent(student);
    printf("\n");
}

// ========================================
// 6. アロー演算子(->)の使い方
// ========================================
void example5_arrow_operator() {
    printf("=== 例5: アロー演算子(->) ===\n");
    
    struct Point p = {5, 10};
    struct Point *ptr = &p;  // ポインタにアドレスを代入
    
    // 3つの書き方（すべて同じ意味）
    printf("方法1（変数直接）: (%d, %d)\n", p.x, p.y);
    printf("方法2（ポインタ+*）: (%d, %d)\n", (*ptr).x, (*ptr).y);
    printf("方法3（アロー演算子）: (%d, %d)\n", ptr->x, ptr->y);
    
    // アロー演算子が一番読みやすい！
    ptr->x = 100;
    ptr->y = 200;
    printf("変更後: (%d, %d)\n\n", p.x, p.y);
}

// ========================================
// 7. 構造体の配列
// ========================================
void example6_array() {
    printf("=== 例6: 構造体の配列 ===\n");
    
    // 構造体の配列を宣言
    struct Student students[3] = {
        {"太郎", 20, 85},
        {"花子", 21, 92},
        {"次郎", 19, 78}
    };
    
    // 配列の各要素にアクセス
    printf("クラスの学生一覧:\n");
    for(int i = 0; i < 3; i++) {
        printf("%d. ", i + 1);
        printStudent(students[i]);
    }
    printf("\n");
}

// ========================================
// 8. 実践例：構造体を使った計算
// ========================================
struct Point addPoints(struct Point p1, struct Point p2) {
    struct Point result;
    result.x = p1.x + p2.x;
    result.y = p1.y + p2.y;
    return result;
}

void example7_practical() {
    printf("=== 例7: 実践例（座標の加算） ===\n");
    
    struct Point p1 = {3, 4};
    struct Point p2 = {5, 6};
    
    struct Point sum = addPoints(p1, p2);
    
    printf("(%d, %d) + (%d, %d) = (%d, %d)\n\n",
           p1.x, p1.y, p2.x, p2.y, sum.x, sum.y);
}

// ========================================
// メイン関数
// ========================================
int main() {
    printf("========================================\n");
    printf("   C言語 構造体の基本\n");
    printf("========================================\n\n");
    
    example1_declaration();
    example2_access();
    example3_function_value();
    example4_pointer();
    example5_arrow_operator();
    example6_array();
    example7_practical();
    
    printf("========================================\n");
    printf("まとめ:\n");
    printf("1. 構造体は複数のデータをまとめる\n");
    printf("2. ドット(.)でメンバにアクセス\n");
    printf("3. ポインタ経由はアロー(->)が便利\n");
    printf("4. 関数に渡すときはポインタ推奨\n");
    printf("========================================\n");
    
    return 0;
}
