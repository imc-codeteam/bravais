@ECHO OFF

rmdir /S bin

REM *************
REM Release build
REM *************
@ECHO *****************
@ECHO Deploying BRAVAIS
@ECHO *****************

REM Create directories
mkdir bin

REM Copy files Bravais
xcopy build-Bravais-Desktop_Qt_5_10_1_MSVC2017_64bit-Release\release\Bravais.exe bin
xcopy bravais.ico bin
if exist C:\Qt\5.10.1\msvc2017_64\bin\windeployqt.exe (
    C:\Qt\5.10.1\msvc2017_64\bin\windeployqt.exe bin\Bravais.exe --release --force
)
if exist D:\Qt\5.10.1\msvc2017_64\bin\windeployqt.exe (
    D:\Qt\5.10.1\msvc2017_64\bin\windeployqt.exe bin\Bravais.exe --release --force
)