@echo off

cl main.c /Ilibs /EHsc /MD /W3 /WX- /D _MBCS /link /NODEFAULTLIB:LIBCMT  OPENGL32.LIB USER32.LIB GDI32.LIB SHELL32.LIB /out:main.exe
