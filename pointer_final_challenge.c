/*
===========================================
  ポインタ最終課題 - 実践編
===========================================

【最終課題】学生管理システム
構造体とポインタを組み合わせた実践的なプログラムを作成してください。

要件:
1. 以下のメンバを持つ構造体 Student を定義する
   - char name[50]  : 名前
   - int age        : 年齢
   - double score   : 点数

2. 以下の関数を作成する:
   
   a) void inputStudent(struct Student *s)
      - ポインタで構造体を受け取る
      - ユーザーから名前、年齢、点数を入力させる
   
   b) void printStudent(struct Student *s)
      - ポインタで構造体を受け取る
      - 学生情報を表示する
   
   c) void updateScore(struct Student *s, double newScore)
      - ポインタで構造体を受け取る
      - 点数を更新する

3. main関数で以下を実行:
   - Student型の変数を1つ宣言
   - inputStudent で情報を入力
   - printStudent で情報を表示
   - updateScore で点数を変更
   - 再度 printStudent で情報を表示

期待される動作例:
=== 学生情報入力 ===
名前: 田中太郎
年齢: 20
点数: 85.5

=== 学生情報 ===
名前: 田中太郎
年齢: 20歳
点数: 85.50点

=== 点数を更新しました ===

=== 学生情報 ===
名前: 田中太郎
年齢: 20歳
点数: 95.00点

ヒント:
- 構造体のメンバにアクセス: (*s).name または s->name
- s->name は (*s).name の省略形（アロー演算子）

===========================================
*/

#include <stdio.h>
#include <string.h>

// ここに構造体 Student を定義してください
struct Student{
    char name[50];
    int age;
    double score;
};

struct Student students;


// ここに関数を作成してください
void inputStudent(struct Student *s){
     printf("=== 学生情報入力 ===\n");
     printf("名前: ");
     scanf("%s",s->name);
     printf("年齢: ");
     scanf("%d",&s->age);
     printf("点数: ");
     scanf("%lf",&s->score);
     printf("\n");
     return;
   }

void printStudent(struct Student *s){
   printf("===学生情報===\n");
   printf("名前: %s\n",s->name);
   printf("年齢: %d歳\n",s->age);
   printf("点数: %.2f点\n",s->score);
   printf("\n");
   return;
}

void updateScore(struct Student *s, double newScore){
   s->score = newScore;
   printf("=== 点数を更新しました ===\n");
   printf("\n");
   return;
}

int main() {
    // ここにコードを書いてください
    int Unum;

    printf("=== 学生情報管理システム ===\n");
    
    while(1){
      printf("=== メニュー ===\n");
      printf("1.学生情報入力\n");
      printf("2.学生情報表示\n");
      printf("3.点数を更新\n");
      printf("4.終了\n");
      printf("input number: ");
      scanf("%d",&Unum);
      printf("\n");

    
      switch(Unum){
        case 1:
           inputStudent(&students);
           continue;
        case 2:
           printStudent(&students);
           continue;
        case 3: {
            double Nscore = 0;
            printf("新しい点数を入力: ");
            scanf("%lf",&Nscore);
            updateScore(&students, Nscore);
            continue;
        }
         case 4:
            printf("システムを終了します\n");
            return 0;
      }
    }
}
