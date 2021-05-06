::CallScript
@echo off
CALL :ScriptA
CALL :ScriptB
CALL :ScriptC
pause
goto :eof


:ScriptA
@ECHO OFF
setlocal EnableDelayedExpansion
set _Output=%UserProfile%\Desktop\MDVR IR numbers\NumGen.txt

::only change these three lines
set "start=883"  ::starts from this number
set "amount=100" ::amount of files created
set "length=5" ::length of fileNames
set "end_with=} " ::what to join each number with
set "Start_with= {" ::what to start each number with


set /a "last=%start%+%amount%"
for /l %%i in (%start%,1,%last%) do (
set "folderName=0000000000%%i"
set "folderName=%start_with%!folderName:~-%length%!%end_with%"
>>"%_Output%" ECHO.!folderName!
)
goto :eof


:ScriptB
@ECHO OFF
    setlocal enableextensions enabledelayedexpansion

    set "var="
    for /f "usebackq delims=" %%a in ("%UserProfile%\Desktop\MDVR IR numbers\NumGen.txt") do set "var=!var!%%a"
    @echo %var%> "%UserProfile%\Desktop\MDVR IR numbers\In.txt"
goto :eof


:ScriptC
@ECHO OFF
del "%UserProfile%\Desktop\MDVR IR numbers\NumGen.txt"
goto :eof
