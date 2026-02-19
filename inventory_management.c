#include<stdio.h>
#include<string.h>

struct Product {
    char name[50];
    int price;
    int stock;
};

struct Product products[10];
int productCount = 0, Ynum = 0;

void addProduct();
void showAllProducts();
void sellProduct(struct Product *p, int sell);
void restockProduct(struct Product *p, int buy);
void showOutOfStock();  //5
void showTotalValue();
void searchProduct();
void deleteProduct();
void changePrice(struct Product *p, int newPrice);

int main(void){
    printf("=== 商品在庫管理システム ===\n");
    printf("\n");
    for(;;){
        printf("\n");
        printf("1. 商品を登録\n");
        printf("2. 全商品を表示\n");
        printf("3. 商品を販売 (在庫を減らす)\n");
        printf("4. 商品を入荷 (在庫を増やす)\n");
        printf("5. 在庫切れ商品を表示\n");
        printf("6. 在庫の合計金額を表示\n");
        printf("7. 商品を検索\n");
        printf("8. 商品を削除\n");
        printf("9. 価格を変更\n");
        printf("10. 終了\n");

        printf("選択してください: ");
        scanf("%d",&Ynum);

        switch(Ynum){
            case 1:
            addProduct();
            break;

            case 2:
            showAllProducts();
            break;

            case 3:{
            int sell = 0;
            printf("商品番号: ");
            scanf("%d",&Ynum);
            printf("販売個数: ");
            scanf("%d",&sell);
            sellProduct(&products[Ynum - 1], sell);
            break;
            }

            case 4:{
            int buy = 0;
            printf("商品番号: ");
            scanf("%d",&Ynum);
            printf("入荷個数: ");
            scanf("%d",&buy);
            restockProduct(&products[Ynum - 1],buy);
            break;
            }

            case 5:
            showOutOfStock();
            break;

            case 6:
            showTotalValue();
            break;

            case 7:
            searchProduct();
            break;
            
            case 8:
            deleteProduct();
            break;

            case 9:
            int num, newPrice;
            printf("商品番号: ");
            scanf("%d",&num);
            printf("新しい価格: ");
            scanf("%d",&newPrice);
            changePrice(&products[num - 1], newPrice);
            break;

            case 10:
            return 0;
        }
    }
}

void addProduct(){
    if(productCount != 10){
        printf("商品名: ");
        scanf("%s",products[productCount].name);
        printf("価格: ");
        scanf("%d",products[productCount].price);
        printf("在庫数: ");
        scanf("%d",products[productCount].stock);
        printf("登録しました！\n");
        productCount++;
    }
    else
        printf("これ以上登録できません。\n");
    return;
}

void showAllProducts(){
    printf("=== 商品一覧 ===\n");
    for(int i = 0; i < productCount; i++){
        printf("%d. %s ",i + 1, products[i].name);
        printf("\t- %d円 (在庫: %d個)\n",products[i].price,products[i].stock);
    }
return;
}

void sellProduct(struct Product *p, int sell){
    
    if((*p).stock - sell >= 0){
        (*p).stock -= sell;
        printf("%sを%d個販売しました。",(*p).name,sell);
        printf("残り在庫: %d個\n",(*p).stock);
        return;
    }
    else{
        printf("在庫より少ない数は販売できません。\n");
        printf("%sの残り在庫: %d個\n",(*p).name, products[Ynum - 1].stock);
        return;
    }
}
//5
void restockProduct(struct Product *p, int buy){
    (*p).stock += buy;
    printf("%sを%d個入荷しました。",(*p).name, buy);
    printf("現在の在庫: %d個\n",(*p).stock);
    return;
}
//6
void showOutOfStock(){
    int frag = 0;
    for(int i = 0; i <productCount; i++){
        if(products[i].stock == 0){
            printf("%sの在庫が0個です。\n",products[i].name);
            frag++;
        }
    }
    if(frag != 0)
        printf("補充してください。\n");
    
    return;
}
//7
void showTotalValue(){
    int sum = 0;
    for(int i = 0; i < productCount; i++){
        sum += products[i].price * products[i].stock;
    }
    printf("在庫の合計金額: %d円\n",sum);

    return;
}

void searchProduct(){
    char searchName[50];
    printf("検索する商品名: ");
    scanf("%s",searchName);

    int found = 0;
    for(int i = 0; i < productCount; i++){
        if(strcmp(products[i].name,searchName) == 0){
            printf("見つかりました！\n");
            printf("%d. %s \t- %d円 (在庫: %d個)\n",i+1,products[i].name, products[i].price, products[i].stock); 
            found = 1;
        }
    break;
    }

    if(found == 0){
        printf("商品が見つかりませんでした。\n");
    }
    return;
}
//8
void deleteProduct(){
    int num;
    printf("削除する商品番号: ");
    scanf("%d",&num);

    if(num < 1 || num > productCount){
        printf("無効な商品番号です。\n");
        return;
    }

    printf("%s を削除しますか？ (1: はい, 0: いいえ): ",products[num-1].name);
    int confirm;
    scanf("%d",&confirm);

    if(confirm != 1){
        printf("削除をキャンセルしました。\n");
        return;
    }

    for(int i = num - 1; i < productCount - 1; i++){
        products[i] = products[i + 1];
    }

    productCount--;
    printf("削除しました！\n");
    return;
}

//9
void changePrice(struct Product *p, int newPrice){
    int oldPrice = (*p).price;
    (*p).price = newPrice;
    printf("%sの価格を変更しました。\n",(*p).name);
    printf("%d → %d\n",oldPrice,newPrice);
    return;
}