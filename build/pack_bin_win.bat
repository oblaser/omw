@rem    author          Oliver Blaser
@rem    date            22.12.2021
@rem    copyright       MIT - Copyright (c) 2021 Oliver Blaser



@rem Result:
@rem 
@rem %SDK%\omw\include\omw\omw.h
@rem %SDK%\omw\include\omw\string.h
@rem %SDK%\omw\include\omw\ etc.
@rem 
@rem %SDK%\omw\lib\omw.lib
@rem %SDK%\omw\lib\omw-d.lib
@rem %SDK%\omw\dll\omw.dll
@rem %SDK%\omw\dll\omw-d.dll
@rem 
@rem %SDK%\omw\lib64\omw.lib
@rem %SDK%\omw\lib64\omw-d.lib
@rem %SDK%\omw\dll64\omw.dll
@rem %SDK%\omw\dll64\omw-d.dll



rmdir /s /q packed\omw_win

xcopy /i /s /e ..\include packed\omw_win\omw\include\

xcopy /i ..\lib\omw-d.lib packed\omw_win\omw\lib\
xcopy /i ..\lib\omw.lib packed\omw_win\omw\lib\
@rem xcopy /i ..\lib64\omw-d.lib packed\omw_win\omw\lib64\
@rem xcopy /i ..\lib64\omw.lib packed\omw_win\omw\lib64\

copy dep_readme.txt packed\omw_win\omw\readme.txt
xcopy ..\license.txt packed\omw_win\omw

cd packed\omw_win
"C:\Program Files\7-Zip\7z.exe" a omw_win_vX.X.X.zip omw\
cd ..\..

move packed\omw_win\omw_win_vX.X.X.zip packed\omw_win_vX.X.X.zip
