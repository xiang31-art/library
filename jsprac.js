let age = 21;

if (age < 0){
    console.log("正の数を指定してください");
}else if (age < 18){
    console.log("未成年です");
}else if (age < 20) {
    console.log("成人ですが、お酒は飲めません");
} else {
    console.log("成人です。お酒も飲めます");
}