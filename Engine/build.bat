@ECHO OFF

call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" x64
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

cls
setlocal ENABLEDELAYEDEXPANSION
SET name=everdone
SET cFilenames=
FOR /R %%f in (*.cpp) do (
    SET cFilenames=!cFilenames! %%f
)
SET cFilenames=!cFilenames! ../../vendor/glad/src/glad.c
REM echo "Files:" %cFilenames%
REM echo "Files:" %cFilenames%

mkdir build

pushd build
ECHO "Building %name%% ..."
REM PRE DEFINES
REM D_DEBUG -DKEXPORT -D_CRT_SECURE_NO_WARNINGS -WINDOWS_PLATFORM /DWINDOWS_PLATFORM
SET defines=/D DEBUG 
REM INCLUDE
set includes=/Isrc
SET includes=!includes! /I%VULKAN_SDK%/Include
SET includes=!includes! /I../../vendor/glad/Include
SET includes=!includes! /I../../vendor/glfw/include
REM LINKERS
REM Shell32.lib for system tray acces
SET linkers=/link 
SET linkers=!linkers! /LIBPATH:../../vendor/glfw-bin/src/Release glfw3.lib opengl32.lib
SET linkers=!linkers! /LIBPATH:%VULKAN_SDK%/Lib vulkan-1.lib
SET linkers=!linkers! User32.lib Gdi32.lib kernel32.lib winspool.lib comdlg32.lib advapi32.lib Shell32.lib

cl -Z7 /W3 /EHsc %includes% %defines% %cFilenames% %linkers% /out:%name%.exe
REM -Zi 
REM /Fe"main"  can change name of something
popd
ECHO "Building %name%% DONE! Finished!"