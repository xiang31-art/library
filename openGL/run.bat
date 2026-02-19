@echo off
call build.bat
if %errorlevel% equ 0 (
    echo.
    echo プログラムを実行します...
    main.exe
)
