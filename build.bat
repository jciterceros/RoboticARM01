@echo off
echo Compilando RoboticARM01 - Versao Modular...

REM Criar diretórios se não existirem
if not exist "bin" mkdir bin
if not exist "obj" mkdir obj
if not exist "obj\robot" mkdir obj\robot

REM Compilar arquivos objeto
echo Compilando joint.c...
gcc -Wall -Wextra -std=c99 -O2 -c src/robot/joint.c -o obj/robot/joint.o

echo Compilando gripper.c...
gcc -Wall -Wextra -std=c99 -O2 -c src/robot/gripper.c -o obj/robot/gripper.o

echo Compilando robot_arm.c...
gcc -Wall -Wextra -std=c99 -O2 -c src/robot/robot_arm.c -o obj/robot/robot_arm.o

echo Compilando Robot.c...
gcc -Wall -Wextra -std=c99 -O2 -c src/Robot.c -o obj/Robot.o

REM Linkar executável
echo Linkando executável...
gcc obj/Robot.o obj/robot/robot_arm.o obj/robot/joint.o obj/robot/gripper.o -o bin/Robot.exe -lopengl32 -lglu32 -lfreeglut

if %ERRORLEVEL% EQU 0 (
    echo.
    echo Compilacao concluida com sucesso!
    echo Executavel criado em: bin/Robot.exe
    echo.
    echo Para executar, use: bin\Robot.exe
) else (
    echo.
    echo Erro na compilacao!
    echo Verifique se o GCC e as bibliotecas OpenGL estao instalados.
)

pause 