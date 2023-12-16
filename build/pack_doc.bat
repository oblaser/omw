@rem    author          Oliver Blaser
@rem    date            16.12.2023
@rem    copyright       MIT - Copyright (c) 2023 Oliver Blaser

rmdir /s /q packed\omw_doc

xcopy /i /s /e ..\doc\out packed\omw_doc

bash -c "source dep_globals.sh && writeReadmeFile packed/omw_doc/readme.txt"
xcopy ..\license.txt packed\omw_doc

cd packed
"C:\Program Files\7-Zip\7z.exe" a omw_doc_vX.X.X.zip omw_doc\
cd ..
