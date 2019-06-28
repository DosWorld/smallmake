@echo off

cc  exesize.c -m -a -p
if errorlevel 1 goto exit
asm exesize.asm
if errorlevel 1 goto exit

val exesize.obj,exesize.exe,,clib.lib
upx -9 --8086 exesize.exe

:exit
