#include<stdio.h>
#include<ctype.h>

struct Book {
    char title[100];
    char author[50];
    int year;
    int price;
    int available;
    int nowAvail;
};


void addBook(struct Book *books, int *count);
void displayBook(struct Book *books, int count);
void borrowBook();
void returnBook();

int main(void){
    struct Book books[10];
    int bookCount = 0;
    int index = 0;
    int Unum = 0;
    int result = 0;     //バリデーションチェック用

    while(1){
        printf("=== 図書管理ツール ===\n");
        printf("\n");
        printf("1.本の追加\n");
        printf("2.本の表示\n");
        printf("3.本の貸し出し\n");
        printf("4.本の返却\n");
        printf("5.終了\n");

        do {
        printf("input number: ");
        result = scanf("%d",&Unum);
        while(getchar() != '\n');

        if(result != 1){
            printf("数値を入力してください\n");
        }
        }while(result != 1);

        printf("\n");
        
        switch(Unum){
            case 1:{
                addBook(books, &bookCount);
                break;
            }

            case 2:{
                displayBook(books,bookCount);
                break;
            }

            case 3:{
                break;
            }

            case 4:{
                break;
            }

            case 5:{
                return 0;
            }
            
            default:{
                printf("予期せぬ値が入力されました\n");
                break;
            }
        }
    }

}

void addBook(struct Book *books, int *count){
    printf("=== 本の追加 ===\n");
    printf("タイトル: ");
    scanf("%s",books[*count].title);
    printf("著者名: ");
    scanf("%s",books[*count].author);
    printf("発売年: ");
    scanf("%d",&books[*count].year);
    printf("価格: ");
    scanf("%d",&books[*count].price);
    printf("在庫: ");
    scanf("%d",&books[*count].available);

    books[*count].nowAvail = books[*count].available;
    printf("nowAvail: %d\n");
    printf("available:%d\n");

    return;
}

void displayBook(struct Book *book, int count){
    printf("=== 本の一覧表示 ===\n\n");

    if(count <= 0){
        printf("表示できる本はありません\n");
        return;
    }
    else{
        for(int i = 0; i <= count; i++){
            printf("--- 本 %d ---\n",i + 1);
            printf("タイトル: %s\n",book[i].title);
            printf("著者名: %s\n",book[i].author);
            printf("発売年: %d\n",book[i].year);
            printf("価格: %d\n",book[i].price);
            printf("在庫: %d\n",book[i].nowAvail);
            printf("\n");
        }
        return;
    }
}

