@rem    author          Oliver Blaser
@rem    date            30.12.2025
@rem    copyright       MIT - Copyright (c) 2025 Oliver Blaser

setlocal

call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\Tools\VsDevCmd.bat"

set ERR=0
set RUN_ONE=0
set BUILD_ALL=0



if "%1"=="" ( goto L_BUILD_ALL_RUN_ONE ) else ( goto L_PROC_NEXT_ARG )



:L_PROC_NEXT_ARG
if not "%1"=="" (
    if /i "%1"=="buildAll" (
        shift
        goto L_BUILD_ALL
    )
    if /i "%1"=="cleanAll" (
        shift
        goto L_CLEAN_ALL
    )
    if /i "%1"=="build86" (
        shift
        goto L_BUILD_86
    )
    if /i "%1"=="build86d" (
        shift
        goto L_BUILD_86D
    )
    if /i "%1"=="build64" (
        shift
        goto L_BUILD_64
    )
    if /i "%1"=="build64d" (
        shift
        goto L_BUILD_64D
    )
    if /i "%1"=="run86" (
        shift
        goto L_RUN_86
    )
    if /i "%1"=="run86d" (
        shift
        goto L_RUN_86D
    )
    if /i "%1"=="run64" (
        shift
        goto L_RUN_64
    )
    if /i "%1"=="run64d" (
        shift
        goto L_RUN_64D
    )

    echo "ERROR: unknown arg: %1"
    goto L_END
) else (
    goto L_END
)

:L_BUILD_ALL_RUN_ONE
set RUN_ONE=1
:L_BUILD_ALL
set BUILD_ALL=1
goto L_BUILD_86



:L_CLEAN_ALL

cd .\vs\
msbuild omw.sln /t:Clean /p:Configuration=Release /p:Platform=x86
if %ERRORLEVEL% neq 0 ( set ERR=1 )
msbuild omw.sln /t:Clean /p:Configuration=Debug /p:Platform=x86
if %ERRORLEVEL% neq 0 ( set ERR=1 )
msbuild omw.sln /t:Clean /p:Configuration=Release /p:Platform=x64
if %ERRORLEVEL% neq 0 ( set ERR=1 )
msbuild omw.sln /t:Clean /p:Configuration=Debug /p:Platform=x64
if %ERRORLEVEL% neq 0 ( set ERR=1 )
cd ..\

if %ERR% neq 0 ( goto L_END )
goto L_PROC_NEXT_ARG



:L_BUILD_86

cd .\vs\
msbuild omw.sln /p:Configuration=Release /p:Platform=x86 /m
if %ERRORLEVEL% neq 0 ( set ERR=1 )
cd ..\

if %ERR% neq 0 ( goto L_END )
if %BUILD_ALL% neq 0 ( goto L_BUILD_86D )
goto L_PROC_NEXT_ARG



:L_BUILD_86D

cd .\vs\
msbuild omw.sln /p:Configuration=Debug /p:Platform=x86 /m
if %ERRORLEVEL% neq 0 ( set ERR=1 )
cd ..\

if %ERR% neq 0 ( goto L_END )
if %BUILD_ALL% neq 0 ( goto L_BUILD_64 )
goto L_PROC_NEXT_ARG



:L_BUILD_64

cd .\vs\
msbuild omw.sln /p:Configuration=Release /p:Platform=x64 /m
if %ERRORLEVEL% neq 0 ( set ERR=1 )
cd ..\

if %ERR% neq 0 ( goto L_END )
if %BUILD_ALL% neq 0 ( goto L_BUILD_64D )
goto L_PROC_NEXT_ARG



:L_BUILD_64D

cd .\vs\
msbuild omw.sln /p:Configuration=Debug /p:Platform=x64 /m
if %ERRORLEVEL% neq 0 ( set ERR=1 )
cd ..\

if %ERR% neq 0 ( goto L_END )
if %RUN_ONE% neq 0 ( goto L_RUN_64 )
goto L_PROC_NEXT_ARG



:L_RUN_86

cd ..\tests\unit\vs\
msbuild omw-tests-unit.sln /p:Configuration=Release /p:Platform=x86 /m
if %ERRORLEVEL% neq 0 ( goto L_END )
cd .\Release\
echo.
echo ###############################################################################
omw-tests-unit.exe
if %ERRORLEVEL% neq 0 ( set ERR=1 )
cd ..\
echo ###############################################################################
cd ..\..\..\build\

if %ERR% neq 0 ( goto L_END )
if %RUN_ONE% neq 0 ( goto L_END )
goto L_PROC_NEXT_ARG



:L_RUN_86D

cd ..\tests\unit\vs\
msbuild omw-tests-unit.sln /p:Configuration=Debug /p:Platform=x86 /m
if %ERRORLEVEL% neq 0 ( goto L_END )
cd .\Debug\
echo.
echo ###############################################################################
omw-tests-unit.exe
if %ERRORLEVEL% neq 0 ( set ERR=1 )
cd ..\
echo ###############################################################################
cd ..\..\..\build\

if %ERR% neq 0 ( goto L_END )
if %RUN_ONE% neq 0 ( goto L_END )
goto L_PROC_NEXT_ARG



:L_RUN_64

cd ..\tests\unit\vs\
msbuild omw-tests-unit.sln /p:Configuration=Release /p:Platform=x64 /m
if %ERRORLEVEL% neq 0 ( goto L_END )
cd .\x64\Release\
echo.
echo ###############################################################################
omw-tests-unit.exe
if %ERRORLEVEL% neq 0 ( set ERR=1 )
cd ..\..\
echo ###############################################################################
cd ..\..\..\build\

if %ERR% neq 0 ( goto L_END )
if %RUN_ONE% neq 0 ( goto L_END )
goto L_PROC_NEXT_ARG



:L_RUN_64D

cd ..\tests\unit\vs\
msbuild omw-tests-unit.sln /p:Configuration=Debug /p:Platform=x64 /m
if %ERRORLEVEL% neq 0 ( goto L_END )
cd .\x64\Debug\
echo.
echo ###############################################################################
omw-tests-unit.exe
if %ERRORLEVEL% neq 0 ( set ERR=1 )
cd ..\..\
echo ###############################################################################
cd ..\..\..\build\

if %ERR% neq 0 ( goto L_END )
if %RUN_ONE% neq 0 ( goto L_END )
goto L_PROC_NEXT_ARG



:L_END
if %RUN_ONE% neq 0 ( pause )

endlocal
