@echo off
cd /d "%~dp0"
python tools\build_compare_view.py --open
if errorlevel 1 pause
