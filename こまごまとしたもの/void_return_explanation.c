#include <stdio.h>

// void関数の例
void greetUser(char name[]);
void printNumbers(int start, int end);
void processArray(int arr[], int size);
void demonstrateReturn(int condition);

int main() {
    printf("=== void Functions and return Statement ===\n\n");
    
    // 1. 基本的なvoid関数
    printf("1. Basic void functions\n");
    greetUser("Alice");
    printNumbers(1, 5);
    printf("\n");
    
    // 2. void関数でのreturnの使い方
    printf("2. Using return in void functions\n");
    demonstrateReturn(1);  // 条件がtrueの場合
    demonstrateReturn(0);  // 条件がfalseの場合
    printf("\n");
    
    // 3. 配列処理のvoid関数
    printf("3. void function with array processing\n");
    int data[5] = {1, 2, 3, 4, 5};
    processArray(data, 5);
    
    return 0;
}

// void関数の実装例

// 1. 基本的なvoid関数（returnなし）
void greetUser(char name[]) {
    printf("Hello, %s!\n", name);
    // returnは書かなくてもOK（自動的に関数終了）
}

// 2. void関数（returnあり、値なし）
void printNumbers(int start, int end) {
    printf("Numbers: ");
    for (int i = start; i <= end; i++) {
        printf("%d ", i);
    }
    printf("\n");
    return;  // 値を返さないreturn（省略可能）
}

// 3. 条件によって早期終了するvoid関数
void demonstrateReturn(int condition) {
    printf("Function called with condition: %d\n", condition);
    
    if (condition == 0) {
        printf("Condition is false, exiting early\n");
        return;  // ここで関数を終了（値は返さない）
    }
    
    printf("Condition is true, continuing execution\n");
    printf("Function completed normally\n");
    // ここでも自動的に関数終了（returnは省略可能）
}

// 4. 配列を処理するvoid関数
void processArray(int arr[], int size) {
    if (size <= 0) {
        printf("Invalid array size\n");
        return;  // エラー時の早期終了
    }
    
    printf("Processing array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i] * 2);  // 各要素を2倍して表示
    }
    printf("\n");
    
    // returnは省略可能（関数の最後で自動終了）
}