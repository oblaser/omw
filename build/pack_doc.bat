@rem    author          Oliver Blaser
@rem    date            09.12.2021
@rem    copyright       MIT - Copyright (c) 2021 Oliver Blaser

rmdir /s /q packed\omw_doc

xcopy /i /s /e ..\doc\out packed\omw_doc

copy dep_readme.txt packed\omw_doc\readme.txt
xcopy ..\license.txt packed\omw_doc

cd packed
"C:\Program Files\7-Zip\7z.exe" a omw_doc_vX.X.X.zip omw_doc\
cd ..
