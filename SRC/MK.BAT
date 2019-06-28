@echo off

del *.asm > nul:
del *.obj > nul:
del make.exe > nul:

cc target.c -m -a -p
if errorlevel 1 goto exit
asm target.asm
if errorlevel 1 goto exit

cc exec.c -m -a -p
if errorlevel 1 goto exit
asm exec.asm
if errorlevel 1 goto exit

cc str.c -m -a -p
if errorlevel 1 goto exit
asm str.asm
if errorlevel 1 goto exit

cc  make.c -m -a -p
if errorlevel 1 goto exit
asm make.asm
if errorlevel 1 goto exit

cc  env.c -m -a -p
if errorlevel 1 goto exit
asm env.asm
if errorlevel 1 goto exit

cc  fio.c -m -a -p
if errorlevel 1 goto exit
asm fio.asm
if errorlevel 1 goto exit

val make.obj+str.obj+target.obj+exec.obj+fio.obj+env.obj,make.exe,,clib.lib
upx -9 --8086 make.exe
exesize make.exe

:exit
