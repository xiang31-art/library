/*
===========================================
  ポインタ基礎 最終チェック課題
===========================================

【課題】図書館管理システム
これまでに学習した全ての要素を使用して、実践的なプログラムを作成してください。

【含まれる学習要素】
1. ポインタの宣言
2. アドレス演算子 &
3. 間接参照演算子 *
4. ポインタへのアドレス代入
5. ポインタで値を変更
6. 配列とポインタの関係
7. ポインタ演算（ptr + i）
8. 構造体の定義
9. 構造体へのポインタ
10. アロー演算子 ->
11. 関数にポインタを渡す
12. 参照渡しで元の値を変更
13. for文でループ処理
14. switch文でメニュー処理
15. printf/scanf でI/O処理

【要件】
1. 以下のメンバを持つ構造体 Book を定義:
   - char title[100]  : 本のタイトル
   - char author[50]  : 著者名
   - int year         : 出版年
   - double price     : 価格
   - int available    : 在庫数（1=在庫あり, 0=在庫なし）

2. 以下の関数を作成:
   
   a) void addBook(struct Book *books, int *count, struct Book newBook)
      - 配列にポインタでアクセス
      - countをポインタで受け取り、冊数を増やす
      - ポインタ演算で配列要素にアクセス
   
   b) void displayBooks(struct Book *books, int count)
      - ポインタで配列にアクセス
      - for文でループ
      - アロー演算子でメンバにアクセス
   
   c) void borrowBook(struct Book *books, int count, int index)
      - ポインタで配列にアクセス
      - 在庫を減らす
      - 在庫がない場合はメッセージを表示
   
   d) void returnBook(struct Book *books, int count, int index)
      - ポインタで配列にアクセス
      - 在庫を増やす

3. main関数で以下を実行:
   - Book型の配列を宣言（最大10冊）
   - int型の変数 bookCount を宣言（初期値0）
   - メニューループで以下を実装:
     * 1: 本を追加
     * 2: 全ての本を表示
     * 3: 本を借りる
     * 4: 本を返す
     * 5: 終了

【期待される動作】
メニューから選択して、本の追加・表示・貸出・返却ができる

【ヒント】
- 配列のポインタ: struct Book *books
- ポインタ演算: books[i] または *(books + i)
- countをポインタで受け取る理由: 関数内で値を変更したいから
- アロー演算子: books[i].title → (books + i)->title

===========================================
*/

#include <stdio.h>
#include <string.h>
#include<unistd.h>

// ここに構造体 Book を定義してください
struct Book{
    char title[100];
    char author[50];
    int year;
    double price;
    int available;
};



// ここに関数を作成してください
void addBook(struct Book *books, int *count, struct Book newBook){
    books[*count] = newBook;
    (*count)++;
    return;
}

void displayBooks(struct Book *books, int count){
   if(count == 0){
      printf("登録されている本はありません\n");
   }
   else{
   printf("=== 蔵書一覧 ===\n");
   printf("%d冊の本が見つかりました\n",count);
   for(int i = 0; i < count; i++){
      printf("=== 本 %d ===\n",i + 1);
      printf("タイトル: %s\n",books[i].title);
      printf("著者名: %s\n",books[i].author);
      printf("出版年: %d\n",books[i].year);
      printf("価格: %.2f\n",books[i].price);
      printf("在庫: %d\n",books[i].available);
      printf("\n");
      }
   }
   return;
}

void borrowBook(struct Book *books, int count, int index){
   if(books[index].available == 0)
      printf("在庫がありません\n");
   else{
      books[index - 1].available -= 1;
      printf("貸出しました\n");
      printf("期限は2週間です\n");
   }
   printf("\n");
   
   return;
}

void returnBook(struct Book *books, int count, int index){
   books[index].available += 1;
   
   int sleep = 25000;
   printf("0%% ");
   usleep(1000000);
   for(int i = 0; i < 20; i++){
   printf("#");
   usleep(sleep);
   }
   printf(" 100%%\n");
   printf("- 返却完了 -\n");
   printf("\n");

   return;
}

int main() {
    // ここにコードを書いてください
    struct Book books[10];
    struct Book newBook;
    int bookCount = 0;
    int Unum = 0;
    int index;

    printf("=== 図書館管理システム ===\n");

    while(1){
        printf("--- メニュー ---\n");
        printf("1.本の追加\n");
        printf("2.すべての本を表示\n");
        printf("3.本を借りる\n");
        printf("4.本を返す\n");
        printf("5.終了\n");

        printf("input number: ");
        scanf("%d",&Unum);
        printf("\n");

            switch(Unum){
                case 1:
                printf("本を登録します\n");
                printf("本の情報を入力してください\n");
                printf("タイトル: ");
                scanf("%s",newBook.title);
                printf("著者名: ");
                scanf("%s",newBook.author);
                printf("出版年: ");
                scanf("%d",&newBook.year);
                printf("価格: ");
                scanf("%lf",&newBook.price);
                printf("在庫: ");
                scanf("%d",&newBook.available);
                addBook(books, &bookCount, newBook);
                break;
                
                case 2:
                displayBooks(books,bookCount);
                break;
                
                case 3:
                printf("=== 本の貸し出し ===\n");
                for(int i = 0; i < bookCount; i++)
                  printf("%d. %s\n",i + 1,books[i].title);
                printf("\n");
                printf("借りたい本の番号を入力してください: ");
                scanf("%d",&index);
                if(index < 0 || index > bookCount){
                  printf("その番号の本はありません\n");
                  break;
                }
                else
                   borrowBook(books,bookCount,index);
                break;

                case 4:
                returnBook(books, bookCount, index);
                break;

                case 5:
                    return 0;
            }
    }
    
        
    return 0;
}
//memo:addBook 配列をfor文回しでコピーするように関数化する