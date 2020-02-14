@echo off
for /l %%i in (1,1,10) do (
cd %%i
echo Compiling binaries for problem %%i...
g++ ./*.cc ./*.h -Wall -o %%i.exe
cd ../
)
echo Compilation complete.