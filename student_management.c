#include<stdio.h>
struct Student{
    char name[50];
    int age;
    int score;
};

struct Student students[5];
int studentCount = 0;

void addStudent();
void showAllStudents();
void showAverage();
void showTopStudent();
void showMenu();

int main(void){
    printf("=== 学生成績管理システム ===\n");
    while(1){
        int Ynum = 0;
        printf("\n");
        printf("1. 学生を登録\n");
        printf("2. 全学生を表示\n");
        printf("3. 平均点を表示\n");
        printf("4. 最高点の学生を表示\n");
        printf("5. 終了\n");

        printf("選択してください: ");
        scanf("%d",&Ynum);
        printf("\n");

        switch(Ynum){
        case 1:
            addStudent();
            continue;
        case 2:
            showAllStudents();
            continue;
        case 3:
            showAverage();
            continue;
        case 4:
            showTopStudent();
            continue;
        case 5:
            printf("プログラムを終了します。");
            return 0;
        default:
            printf("指定以外の数値が入力されました\n");
            printf("メニューに戻ります\n");
            showMenu();
        }
    }
}

void addStudent(){
    if(studentCount >= 5){
        printf("これ以上登録できません（最大5人）\n");
        return;
    }
    printf("学生を登録します\n");
    printf("name: ");
    scanf("%s",students[studentCount].name);
    printf("age: ");
    scanf("%d",&students[studentCount].age);
    printf("score: ");
    scanf("%d",&students[studentCount].score);

    studentCount++;
    printf("登録しました！\n");
    return;
}

void showAllStudents(){
    if(studentCount == 0){
        printf("まだ学生が登録されていません\n");
        return;
    }
    printf("\n=== 登録学生一覧 ===\n");
    for(int i = 0; i < studentCount; i++){
        printf("%d. %s ",i+1, students[i].name);
        printf("(%d歳) - %d点\n",students[i].age, students[i].score);
    }
    return;
}

void showAverage(){
    double sum = 0, ave = 0;
    for(int i = 0; i < studentCount; i++){
        sum += students[i].score;
    }

    ave = (double)sum / studentCount;
    printf("平均点: %.2f点\n",ave);

    return;
}

void showTopStudent(){
    int maxScore = students[0].score;
    int maxIndex = 0;
    for(int i = 1; i < studentCount; i++){
        if(maxScore < students[i].score){
            maxScore = students[i].score;
            maxIndex = i;
        }
    }
    printf("最高点: %s ",students[maxIndex].name);
    printf("(%d歳) - %d点\n",students[maxIndex].age,students[maxIndex].score);

    return;
}

void showMenu(){
    return;
}