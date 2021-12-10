@rem    author          Oliver Blaser
@rem    date            10.12.2021
@rem    copyright       MIT - Copyright (c) 2021 Oliver Blaser

rmdir /s /q built\omw_win

@rem Result:
@rem 
@rem %SDK%\omw\include\omw\omw.h
@rem %SDK%\omw\include\omw\string.h
@rem %SDK%\omw\include\omw\ etc.
@rem 
@rem %SDK%\omw\lib_x86\omw.lib
@rem %SDK%\omw\lib_x86\omw-d.lib
@rem 
@rem %SDK%\omw\lib_x64\omw.lib
@rem %SDK%\omw\lib_x64\omw-d.lib
@rem 
@rem %SDK%\omw\dll_x86\omw.dll
@rem %SDK%\omw\dll_x86\omw-d.dll
@rem 
@rem %SDK%\omw\dll_x64\omw.dll
@rem %SDK%\omw\dll_x64\omw-d.dll



xcopy /i /s /e ..\include built\omw_win\omw\include\

xcopy /i built\win_Win32_Debug\omw-d.lib built\omw_win\omw\lib_x86\
xcopy /i built\win_Win32_Release\omw.lib built\omw_win\omw\lib_x86\

copy release_readme.txt built\omw_win\omw\readme.txt
xcopy ..\license.txt built\omw_win\omw

cd built\omw_win
"C:\Program Files\7-Zip\7z.exe" a omw_win_vX.X.X.zip omw\
cd ..\..

move built\omw_win\omw_win_vX.X.X.zip built\omw_win_vX.X.X.zip
