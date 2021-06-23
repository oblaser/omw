@rem    author         Oliver Blaser
@rem    date           21.06.2021
@rem    copyright      MIT - Copyright (c) 2021 Oliver Blaser

rmdir /s /q built\omw_src

xcopy /i /s /e ..\include built\omw_src\include
xcopy /i /s /e ..\src built\omw_src\src

cd built
"C:\Program Files\7-Zip\7z.exe" a omw_src_vX.X.X.zip omw_src\
cd ..
