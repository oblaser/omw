@rem    author          Oliver Blaser
@rem    date            09.12.2021
@rem    copyright       MIT - Copyright (c) 2021 Oliver Blaser

rmdir /s /q built\omw_src

xcopy /i /s /e ..\include built\omw_src\omw\include
xcopy /i /s /e ..\src built\omw_src\omw\src

copy release_readme.txt built\omw_src\omw\readme.txt
xcopy ..\license.txt built\omw_src\omw

cd built\omw_src
"C:\Program Files\7-Zip\7z.exe" a omw_src_vX.X.X.zip omw\
cd ..\..

move built\omw_src\omw_src_vX.X.X.zip built\omw_src_vX.X.X.zip
