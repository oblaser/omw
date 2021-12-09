@rem    author          Oliver Blaser
@rem    date            09.12.2021
@rem    copyright       MIT - Copyright (c) 2021 Oliver Blaser

rmdir /s /q built\omw_doc

xcopy /i /s /e ..\doc\out built\omw_doc

copy release_readme.txt built\omw_doc\readme.txt
xcopy ..\license.txt built\omw_doc

cd built
"C:\Program Files\7-Zip\7z.exe" a omw_doc_vX.X.X.zip omw_doc\
cd ..
