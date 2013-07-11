@echo off


rem --- using: MS VC++ 2005 ---


set COMPILE_OPTIONS=/c /O2 /GL /arch:SSE /fp:fast /EHsc /GR- /GS- /MT /W4 /WL /nologo /DTESTING



@echo.
@echo --- compile --

cl %COMPILE_OPTIONS% PowFast.c
cl %COMPILE_OPTIONS% PowFast-tester.c



@echo.
@echo --- link --

link /LTCG /OPT:REF /OPT:NOWIN98 /NOLOGO /OUT:PowFast-tester_c.exe kernel32.lib *.obj



del /Q *.obj
