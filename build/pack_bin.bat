@rem    author          Oliver Blaser
@rem    date            21.12.2021
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



rmdir /s /q built\omw_win

xcopy /i /s /e ..\include built\omw_win\omw\include\

xcopy /i ..\lib\omw-d.lib built\omw_win\omw\lib\
xcopy /i ..\lib\omw.lib built\omw_win\omw\lib\

copy release_readme.txt built\omw_win\omw\readme.txt
xcopy ..\license.txt built\omw_win\omw

cd built\omw_win
"C:\Program Files\7-Zip\7z.exe" a omw_win_vX.X.X.zip omw\
cd ..\..

move built\omw_win\omw_win_vX.X.X.zip built\omw_win_vX.X.X.zip
