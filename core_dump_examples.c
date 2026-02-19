#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ========================================
// 例1：NULL ポインタアクセス
// ========================================
void example1_null_pointer() {
    printf("\n=== 例1: NULL ポインタアクセス ===\n");
    
    int *ptr = NULL;
    int value = 42;
    
    printf("ptr = %p\n", (void*)ptr);
    printf("value = %d\n", value);
    printf("NULL ポインタにアクセスします...\n");
    
    *ptr = 100;  // ここでクラッシュ
    
    printf("この行は実行されません\n");
}

// ========================================
// 例2：配列の境界外アクセス
// ========================================
void example2_buffer_overflow() {
    printf("\n=== 例2: 配列の境界外アクセス ===\n");
    
    int arr[5] = {10, 20, 30, 40, 50};
    int index = 1000000;
    
    printf("配列サイズ: 5\n");
    printf("アクセスするインデックス: %d\n", index);
    
    for (int i = 0; i < 5; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }
    
    printf("arr[%d] にアクセスします...\n", index);
    arr[index] = 99;  // ここでクラッシュ
    
    printf("この行は実行されません\n");
}

// ========================================
// 例3：ダングリングポインタ
// ========================================
void example3_dangling_pointer() {
    printf("\n=== 例3: ダングリングポインタ ===\n");
    
    int *ptr = malloc(sizeof(int) * 10);
    if (ptr == NULL) {
        printf("メモリ割り当て失敗\n");
        return;
    }
    
    printf("メモリを割り当てました: %p\n", (void*)ptr);
    
    for (int i = 0; i < 10; i++) {
        ptr[i] = i * 10;
    }
    
    printf("ptr[0] = %d\n", ptr[0]);
    printf("ptr[5] = %d\n", ptr[5]);
    
    printf("メモリを解放します...\n");
    free(ptr);
    
    printf("解放後にアクセスします...\n");
    ptr[0] = 999;  // ここでクラッシュ（または不正な動作）
    
    printf("この行は実行されません\n");
}

// ========================================
// 例4：スタックトレースの確認
// ========================================
void level3() {
    int level3_var = 300;
    printf("level3: level3_var = %d\n", level3_var);
    
    int *ptr = NULL;
    printf("NULL ポインタにアクセスします...\n");
    *ptr = 10;  // ここでクラッシュ
}

void level2() {
    int level2_var = 200;
    printf("level2: level2_var = %d\n", level2_var);
    level3();
}

void level1() {
    int level1_var = 100;
    printf("level1: level1_var = %d\n", level1_var);
    level2();
}

void example4_stack_trace() {
    printf("\n=== 例4: スタックトレースの確認 ===\n");
    
    int main_var = 10;
    printf("main_var = %d\n", main_var);
    level1();
    
    printf("この行は実行されません\n");
}

// ========================================
// 例5：構造体とコアダンプ
// ========================================
typedef struct {
    int id;
    char name[50];
    float score;
    int *grades;
} Student;

void example5_struct_crash() {
    printf("\n=== 例5: 構造体とコアダンプ ===\n");
    
    Student student;
    student.id = 12345;
    strcpy(student.name, "Yamada Taro");
    student.score = 95.5f;
    student.grades = malloc(sizeof(int) * 5);
    
    if (student.grades != NULL) {
        for (int i = 0; i < 5; i++) {
            student.grades[i] = 80 + i * 5;
        }
    }
    
    printf("学生ID: %d\n", student.id);
    printf("名前: %s\n", student.name);
    printf("スコア: %.1f\n", student.score);
    
    if (student.grades != NULL) {
        printf("成績: ");
        for (int i = 0; i < 5; i++) {
            printf("%d ", student.grades[i]);
        }
        printf("\n");
    }
    
    // 意図的にクラッシュ
    int *bad_ptr = NULL;
    printf("NULL ポインタにアクセスします...\n");
    *bad_ptr = 10;  // ここでクラッシュ
    
    free(student.grades);
    printf("この行は実行されません\n");
}

// ========================================
// 例6：複雑なデータ構造
// ========================================
typedef struct Node {
    int data;
    struct Node *next;
} Node;

void example6_linked_list() {
    printf("\n=== 例6: リンクリストとコアダンプ ===\n");
    
    // リンクリストを作成
    Node *head = malloc(sizeof(Node));
    head->data = 1;
    head->next = malloc(sizeof(Node));
    head->next->data = 2;
    head->next->next = malloc(sizeof(Node));
    head->next->next->data = 3;
    head->next->next->next = NULL;
    
    // リストを表示
    printf("リンクリスト: ");
    Node *current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
    
    // 意図的に不正なポインタを作成
    Node *bad_node = (Node *)0x12345678;
    printf("不正なノードにアクセスします...\n");
    printf("bad_node->data = %d\n", bad_node->data);  // ここでクラッシュ
    
    // メモリ解放（実行されない）
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
}

// ========================================
// メイン関数
// ========================================
int main() {
    printf("╔════════════════════════════════════════════════════════╗\n");
    printf("║         コアダンプ解析用サンプルプログラム            ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n");
    
    printf("\nこのプログラムは意図的にクラッシュします\n");
    printf("コアダンプを生成して gdb で解析してください\n\n");
    
    printf("実行する例を選択してください:\n");
    printf("1: NULL ポインタアクセス\n");
    printf("2: 配列の境界外アクセス\n");
    printf("3: ダングリングポインタ\n");
    printf("4: スタックトレースの確認\n");
    printf("5: 構造体とコアダンプ\n");
    printf("6: リンクリストとコアダンプ\n");
    printf("0: 終了\n");
    printf("選択: ");
    
    int choice;
    if (scanf("%d", &choice) != 1) {
        printf("入力エラー\n");
        return 1;
    }
    
    switch (choice) {
        case 1:
            example1_null_pointer();
            break;
        case 2:
            example2_buffer_overflow();
            break;
        case 3:
            example3_dangling_pointer();
            break;
        case 4:
            example4_stack_trace();
            break;
        case 5:
            example5_struct_crash();
            break;
        case 6:
            example6_linked_list();
            break;
        case 0:
            printf("プログラムを終了します\n");
            return 0;
        default:
            printf("無効な選択です\n");
            return 1;
    }
    
    printf("\n=== プログラムが正常に終了しました ===\n");
    return 0;
}
