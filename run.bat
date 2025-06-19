@echo off
cd /d %~dp0

REM Executar o app (independente do resultado do build)
if exist bin\Robot.exe (
    echo Iniciando o app...
    cd bin
    Robot.exe
    cd ..
) else (
    echo Erro: bin\Robot.exe nao encontrado!
) 