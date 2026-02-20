#include <stdio.h>
#include <string.h>

/*
========================================
アロー演算子（->）完全ガイド
========================================
ポインタ経由で構造体のメンバにアクセスする便利な記法
*/

// 学生情報の構造体
struct Student {
    char name[50];
    int age;
    int score;
};

// ========================================
// 1. ドット演算子とアロー演算子の違い
// ========================================
void example1_difference() {
    printf("=== 例1: ドット(.)とアロー(->)の違い ===\n");
    
    // 普通の構造体変数
    struct Student student = {"田中", 20, 85};
    
    // ドット演算子(.)を使う
    printf("名前: %s\n", student.name);
    printf("年齢: %d\n", student.age);
    printf("点数: %d\n", student.score);
    
    // ポインタを作る
    struct Student *ptr = &student;
    
    // アロー演算子(->)を使う
    printf("\nポインタ経由:\n");
    printf("名前: %s\n", ptr->name);
    printf("年齢: %d\n", ptr->age);
    printf("点数: %d\n\n", ptr->score);
    
    // まとめ:
    // 変数.メンバ     ← 変数を直接使う
    // ポインタ->メンバ ← ポインタ経由で使う
}

// ========================================
// 2. アロー演算子の正体
// ========================================
void example2_truth() {
    printf("=== 例2: アロー演算子の正体 ===\n");
    
    struct Student student = {"佐藤", 22, 90};
    struct Student *ptr = &student;
    
    // 以下の3つは全く同じ意味！
    printf("方法1（変数直接）: %s\n", student.name);
    printf("方法2（*とドット）: %s\n", (*ptr).name);
    printf("方法3（アロー）  : %s\n", ptr->name);
    
    printf("\n");
    printf("つまり:\n");
    printf("ptr->name は (*ptr).name の省略形！\n");
    printf("アロー演算子の方が読みやすい！\n\n");
}

// ========================================
// 3. 関数でアロー演算子を使う
// ========================================
void printStudent(struct Student *s) {
    // ポインタで受け取るので、アロー演算子を使う
    printf("%s (年齢: %d, 点数: %d)\n", s->name, s->age, s->score);
}

void updateScore(struct Student *s, int newScore) {
    // アロー演算子で値を変更
    s->score = newScore;
}

void example3_function() {
    printf("=== 例3: 関数でアロー演算子を使う ===\n");
    
    struct Student student = {"鈴木", 21, 75};
    
    printf("変更前: ");
    printStudent(&student);
    
    // ポインタを渡して、元の変数を変更
    updateScore(&student, 95);
    
    printf("変更後: ");
    printStudent(&student);
    printf("\n");
}

// ========================================
// 4. なぜアロー演算子が必要？
// ========================================
void example4_why() {
    printf("=== 例4: なぜアロー演算子が必要？ ===\n");
    
    struct Student student = {"山田", 19, 80};
    struct Student *ptr = &student;
    
    // 間違った書き方
    // printf("%s\n", ptr.name);  // エラー！ptrはポインタ
    
    // 正しい書き方（でも読みにくい）
    printf("(*ptr).nameの書き方: %s\n", (*ptr).name);
    // 括弧が必要！ *ptr.name だと意味が変わる
    
    // 正しい書き方（読みやすい！）
    printf("ptr->nameの書き方  : %s\n", ptr->name);
    
    printf("\n理由: アロー演算子の方が簡潔で読みやすい！\n\n");
}

// ========================================
// 5. 値の変更
// ========================================
void example5_modify() {
    printf("=== 例5: アロー演算子で値を変更 ===\n");
    
    struct Student student = {"高橋", 23, 70};
    struct Student *ptr = &student;
    
    printf("変更前: %s, %d歳, %d点\n", ptr->name, ptr->age, ptr->score);
    
    // アロー演算子で値を変更
    ptr->age = 24;
    ptr->score = 88;
    strcpy(ptr->name, "高橋太郎");
    
    printf("変更後: %s, %d歳, %d点\n", ptr->name, ptr->age, ptr->score);
    printf("\n");
}

// ========================================
// 6. 配列とアロー演算子
// ========================================
void example6_array() {
    printf("=== 例6: 配列とアロー演算子 ===\n");
    
    struct Student students[3] = {
        {"太郎", 20, 85},
        {"花子", 21, 92},
        {"次郎", 19, 78}
    };
    
    // 配列の先頭アドレスをポインタに代入
    struct Student *ptr = students;
    
    // ポインタで配列の要素にアクセス
    printf("1人目: ");
    printStudent(ptr);  // ptr は students[0] を指す
    
    printf("2人目: ");
    printStudent(ptr + 1);  // ptr + 1 は students[1] を指す
    
    printf("3人目: ");
    printStudent(ptr + 2);  // ptr + 2 は students[2] を指す
    
    printf("\n");
}

// ========================================
// 7. 実践例：複数の学生の平均点を計算
// ========================================
double calculateAverage(struct Student *students, int count) {
    int total = 0;
    
    for(int i = 0; i < count; i++) {
        // (students + i)->score でi番目の学生の点数にアクセス
        total += (students + i)->score;
    }
    
    return (double)total / count;
}

void example7_practical() {
    printf("=== 例7: 実践例（平均点計算） ===\n");
    
    struct Student class[4] = {
        {"Aさん", 20, 85},
        {"Bさん", 21, 90},
        {"Cさん", 19, 78},
        {"Dさん", 22, 88}
    };
    
    double average = calculateAverage(class, 4);
    
    printf("クラスの平均点: %.2f点\n\n", average);
}

// ========================================
// 8. よくある間違い
// ========================================
void example8_mistakes() {
    printf("=== 例8: よくある間違い ===\n");
    
    struct Student student = {"伊藤", 20, 85};
    struct Student *ptr = &student;
    
    printf("正しい使い方:\n");
    printf("変数の場合  : student.name → %s\n", student.name);
    printf("ポインタの場合: ptr->name    → %s\n", ptr->name);
    
    printf("\n間違った使い方:\n");
    printf("❌ ptr.name     （ptrはポインタなのでドットは使えない）\n");
    printf("❌ student->name （studentは変数なのでアローは使えない）\n");
    printf("❌ *ptr.name    （括弧が必要: (*ptr).name）\n");
    printf("\n");
}

// ========================================
// メイン関数
// ========================================
int main() {
    printf("========================================\n");
    printf("   アロー演算子（->）完全ガイド\n");
    printf("========================================\n\n");
    
    example1_difference();
    example2_truth();
    example3_function();
    example4_why();
    example5_modify();
    example6_array();
    example7_practical();
    example8_mistakes();
    
    printf("========================================\n");
    printf("まとめ:\n");
    printf("========================================\n");
    printf("1. 変数.メンバ     ← 変数を直接使う\n");
    printf("2. ポインタ->メンバ ← ポインタ経由で使う\n");
    printf("\n");
    printf("3. ptr->name は (*ptr).name と同じ\n");
    printf("4. アロー演算子の方が読みやすい\n");
    printf("5. 関数でポインタを使うときに便利\n");
    printf("========================================\n");
    
    return 0;
}

/*
========================================
チートシート
========================================

【使い分け】
struct Student s;      // 変数
struct Student *ptr;   // ポインタ

s.name      ← 変数はドット(.)
ptr->name   ← ポインタはアロー(->)

【同じ意味】
ptr->name
(*ptr).name
これらは完全に同じ！アローの方が簡潔

【よくあるパターン】
// 関数でポインタを受け取る
void func(struct Student *s) {
    s->name   // アロー演算子を使う
    s->age
    s->score
}

// 関数を呼ぶとき
struct Student student;
func(&student);  // アドレスを渡す

【覚え方】
ポインタ（→）だからアロー（->）！
*/
