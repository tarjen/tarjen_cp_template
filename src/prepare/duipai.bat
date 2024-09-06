@echo off
setlocal enabledelayedexpansion

set T=0
:loop
if %T% gtr 100000 (
    echo "Finished"
    exit /b
)
set /a T+=1
echo T=!T!
testin.exe > data.txt
abiaocheng.exe < data.txt > biaoda.txt
nedtest.exe < data.txt > aatest.txt

fc aatest.txt biaoda.txt
if errorlevel 1 (
    echo "WA"
    exit /b
)

goto loop