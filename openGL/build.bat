@echo off
gcc main.c -o main.exe -I"C:/Program Files (x86)/mingw64/include" -L"C:/Program Files (x86)/mingw64/lib" -lglfw3 -lglew32 -lopengl32 -lgdi32
if %errorlevel% equ 0 (
    echo コンパイル成功！
) else (
    echo コンパイル失敗
)
