@echo off
make 1>&2
if %errorlevel% neq 0 exit /b %errorlevel%
bot.exe

