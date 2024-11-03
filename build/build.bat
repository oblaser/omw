@rem    author          Oliver Blaser
@rem    date            03.11.2024
@rem    copyright       MIT - Copyright (c) 2024 Oliver Blaser

setlocal

call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\Tools\VsDevCmd.bat"



cd .\vs\
msbuild omw.sln /p:Configuration=Debug /p:Platform=x86
msbuild omw.sln /p:Configuration=Release /p:Platform=x86
msbuild omw.sln /p:Configuration=Debug /p:Platform=x64
msbuild omw.sln /p:Configuration=Release /p:Platform=x64
cd ..\



cd ..\tests\unit\vs\

msbuild omw-tests-unit.sln /p:Configuration=Release /p:Platform=x86
cd .\Release\
echo.
echo ###############################################################################
omw-tests-unit.exe
cd ..\
echo ###############################################################################

msbuild omw-tests-unit.sln /p:Configuration=Release /p:Platform=x64
cd .\x64\Release\
echo.
echo ###############################################################################
omw-tests-unit.exe
cd ..\..\
echo ###############################################################################

cd ..\..\..\build\



endlocal
