@echo off
rem Script de compilação para RoboticARM01
set "SRC_DIR=src"
set "ROBOT_DIR=%SRC_DIR%\\robot"
set "INPUT_DIR=%SRC_DIR%\\input"
set "OBJ_DIR=obj"
set "BIN_DIR=bin"
set "TARGET=%BIN_DIR%\\Robot.exe"
set "GRAPHICS_DIR=%SRC_DIR%\\graphics"

set "SOURCES=%SRC_DIR%\\Robot.c %ROBOT_DIR%\\joint.c %ROBOT_DIR%\\gripper.c %ROBOT_DIR%\\robot_arm.c %INPUT_DIR%\\input_handler.c %GRAPHICS_DIR%\\graphics_init.c"

set "CC=gcc"
set "CFLAGS=-Iinclude -Wall -Wextra -O2"
set "LDFLAGS=-lopengl32 -lglu32 -lfreeglut"

rem --- Início do Script ---
echo Compilando RoboticARM01 - Versao Modular...

rem Cria os diretórios se não existirem
if not exist "%OBJ_DIR%" mkdir "%OBJ_DIR%"
if not exist "%BIN_DIR%" mkdir "%BIN_DIR%"
if not exist "%OBJ_DIR%\\robot" mkdir "%OBJ_DIR%\\robot"
if not exist "%OBJ_DIR%\\input" mkdir "%OBJ_DIR%\\input"
if not exist "%OBJ_DIR%\\graphics" mkdir "%OBJ_DIR%\\graphics"


rem Compila todos os fontes para objetos
%CC% %CFLAGS% -c %SRC_DIR%\\Robot.c -o %OBJ_DIR%\\Robot.o
%CC% %CFLAGS% -c %ROBOT_DIR%\\joint.c -o %OBJ_DIR%\\robot\\joint.o
%CC% %CFLAGS% -c %ROBOT_DIR%\\gripper.c -o %OBJ_DIR%\\robot\\gripper.o
%CC% %CFLAGS% -c %ROBOT_DIR%\\robot_arm.c -o %OBJ_DIR%\\robot\\robot_arm.o
%CC% %CFLAGS% -c %INPUT_DIR%\\input_handler.c -o %OBJ_DIR%\\input\\input_handler.o
%CC% %CFLAGS% -c %GRAPHICS_DIR%\\graphics_init.c -o %OBJ_DIR%\\graphics\\graphics_init.o


rem Linka os objetos para criar o executável
echo Linkando executável...
set "OBJECTS=%OBJ_DIR%\\Robot.o %OBJ_DIR%\\robot\\joint.o %OBJ_DIR%\\robot\\gripper.o %OBJ_DIR%\\robot\\robot_arm.o %OBJ_DIR%\\input\\input_handler.o %OBJ_DIR%\\graphics\\graphics_init.o"
%CC% %OBJECTS% -o %TARGET% %LDFLAGS%

if %errorlevel% neq 0 (
    echo.
    echo Erro na compilacao!
    echo Verifique se o GCC e as bibliotecas OpenGL estao instalados.
    pause
    exit /b 1
)

echo.
echo Compilacao concluida com sucesso!
echo Executavel criado em %TARGET%
rem pause 