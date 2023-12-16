@rem    author          Oliver Blaser
@rem    date            16.12.2023
@rem    copyright       MIT - Copyright (c) 2023 Oliver Blaser

rmdir /s /q packed\omw_src

xcopy /i /s /e ..\include packed\omw_src\omw\include
xcopy /i /s /e ..\src packed\omw_src\omw\src

bash -c "source dep_globals.sh && writeReadmeFile packed/omw_src/omw/readme.txt"
xcopy ..\license.txt packed\omw_src\omw

cd packed\omw_src
"C:\Program Files\7-Zip\7z.exe" a omw_src_vX.X.X.zip omw\
cd ..\..

move packed\omw_src\omw_src_vX.X.X.zip packed\omw_src_vX.X.X.zip
