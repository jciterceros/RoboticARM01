@echo off
cd /d %~dp0

REM Caminhos
set SRC=../src
set BIN=../bin

REM Compilar usando MSYS2 UCRT64
C:\msys64\msys2_shell.cmd -defterm -here -no-start -ucrt64 -c "gcc %SRC%/Robot.c -o %BIN%/Robot.exe -I%SRC% -lfreeglut -lopengl32 -lglu32 -lwinmm -lgdi32"

if %ERRORLEVEL% EQU 0 (
    echo Compilacao bem-sucedida!
    if exist %BIN%\Robot.exe (
        echo Executavel criado: %BIN%\Robot.exe
        echo.
        echo Executando o programa...
        echo.
        echo CONTROLES:
        echo - Setas: Controlar o braco robotico
        echo - Mouse: Rotacionar a visualizacao
        echo - ESC: Sair
        echo.
        pushd %BIN%
        Robot.exe
        popd
    ) else (
        echo AVISO: Executavel nao encontrado!
    )
) else (
    echo Erro na compilacao!
    echo Codigo de erro: %ERRORLEVEL%
)

pause 