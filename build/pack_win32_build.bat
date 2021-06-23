@rem    author         Oliver Blaser
@rem    date           21.06.2021
@rem    copyright      MIT - Copyright (c) 2021 Oliver Blaser

rmdir /s /q built\omw_win32

xcopy /i /s /e ..\include built\omw_win32\include

xcopy /i built\win_Win32_Debug\omw-d.lib built\omw_win32\lib\
xcopy /i built\win_Win32_Release\omw.lib built\omw_win32\lib\

cd built
"C:\Program Files\7-Zip\7z.exe" a omw_win32_vX.X.X.zip omw_win32\
cd ..
