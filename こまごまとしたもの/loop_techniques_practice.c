#include <stdio.h>

int main() {
    printf("=== Loop Techniques Practice ===\n\n");
    
    // 課題1: 3重ループで立方体の合計を求める
    printf("Exercise 1: Calculate sum of 3D array using triple loop\n");
    int data[2][2][3] = {
        {{1, 2, 3}, {4, 5, 6}},
        {{7, 8, 9}, {10, 11, 12}}
    };
    
    printf("3D array structure:\n");
    // ここに3重ループで配列の内容を表示するコードを書いてください
    for(int i=0; i<2; i++){  // 修正: i<2
        printf("Layer %d:\n",i);
        for(int j=0; j<2; j++){  // 修正: j<2
            printf("  Row %d:",j);
            for(int k=0; k<3; k++){  // 修正: k<3
                printf("%3d",data[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
    
    int total_sum = 0;
    // ここに3重ループで合計を計算するコードを書いてください
    for(int i=0; i<2; i++){
        for(int j=0; j<2; j++){
            for(int k=0; k<3; k++){
                total_sum += data[i][j][k];
            }
        }
    }
    
    printf("Total sum: %d\n\n", total_sum);
    
    // 課題2: break文を使って素数を見つける
    printf("Exercise 2: Find first prime number after 20 using break\n");
    // ここにコードを書いてください
    // ヒント: 素数は2以上の数で、1と自分自身以外で割り切れない数
    for(int i=21; i<=50; i++){
        int is_prime = 1;  // 修正: 毎回リセット
        for(int j=2; j<i; j++){  // 修正: j<i
            if(i % j == 0){
                is_prime = 0;
                break;
            }
        }
        if(is_prime){
            printf("Found first prime: %d\n",i);
            break;
        }
    }
    
    printf("\n");
    
    // 課題3: continue文を使って3の倍数以外を表示
    printf("Exercise 3: Print numbers 1-20 except multiples of 3\n");
    // ここにコードを書いてください
    for(int i=1; i<=20; i++){  // 修正: i=1から開始
        if(i % 3 == 0){
            continue;
        }
        printf("%d ", i);  // 修正: iを表示
    }
    printf("\n");  // 追加: 最後に改行
    
    printf("\n");
    
    // 課題4: 多重ループからの脱出
    printf("Exercise 4: Find coordinates where x+y = 10 and x*y = 21\n");
    printf("Searching in range 1-15...\n");
    // ここにコードを書いてください
    // ヒント: goto文またはフラグ変数を使用
    for(int i=1; i<=15; i++){
        for(int j=1; j<=15; j++){
            if(i+j == 10 && i*j == 21){
                printf("found (x,y) = (%d,%d)\n",i,j);
                goto found_result;
            }
        }
    }
    found_result:
    
    printf("\n");
    
    // 課題5: ループ最適化
    printf("Exercise 5: Optimized factorial calculation\n");
    printf("Calculate factorial of numbers 1 to 10:\n");
    // ここにコードを書いてください
    // ヒント: 前の結果を使って効率化
    int factorial = 1;  // 修正: 1で初期化
    for(int i=1; i<=10; i++){
        factorial *= i;
        printf("%2d! = %d\n", i, factorial);  // 修正: 各階乗を表示
    }

    return 0;
}