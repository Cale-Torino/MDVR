@echo off
set "InFile=%USERPROFILE%\Desktop\MDVR IR numbers\In.txt"
set "OutPutFile=%USERPROFILE%\Desktop\MDVR IR numbers\Out.txt"

copy "%InFile%" "%OutPutFile%"
CALL :replace   0   M
CALL :replace   1   N
CALL :replace   2   O
CALL :replace   3   P
CALL :replace   4   Q
CALL :replace   5   R    
CALL :replace   6   S
CALL :replace   7   T
CALL :replace   8   U
CALL :replace   9   V

CALL :replace   M   " 0x1067728D, "
CALL :replace   N   " 0x106742BD, "
CALL :replace   O   " 0x1067827D, "
CALL :replace   P   " 0x106702FD, "
CALL :replace   Q   " 0x1067629D, "
CALL :replace   R   " 0x1067A25D, "
CALL :replace   S   " 0x106722DD, "
CALL :replace   T   " 0x106752AD, "
CALL :replace   U   " 0x1067926D, "
CALL :replace   V   " 0x106712ED, "
CALL :replace   ",}"   }
goto :eof

:replace
@echo off
set "OldStr=%~1"
set "NewStr=%~2"
Call :FindReplace "%OldStr%" "%NewStr%" "%OutPutFile%"
exit /b

:FindReplace <OldStr> <NewStr> <InFile> <OutPutFile>
SETLOCAL ENABLEEXTENSIONS, DisableDelayedExpansion
rem if "%~1"=="" findstr "^::" "%~f0"&GOTO:EOF
(
    for /f "tokens=*" %%A in ('findstr /n "^" %3') do (
        set "line=%%A"
        setlocal EnableDelayedExpansion
        set "line=!line:*:=!"
        if defined line (
            set "line=!line:%~1=%~2!"
        )
        (echo(!line!)
        endlocal
    )
) > TEMPFILE.tmp
del "%~3"
move TEMPFILE.tmp "%~3"
goto :eof