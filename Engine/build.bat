@ECHO OFF

call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
cls
setlocal ENABLEDELAYEDEXPANSION
SET name=everdone
SET cFilenames=
FOR /R %%f in (*.cpp) do (
    SET cFilenames=!cFilenames! %%f
)
REM echo "Files:" %cFilenames%
REM echo "Files:" %cFilenames%

mkdir build
pushd build

ECHO "Building %name%%..."
REM SET defines=/DWINDOWS_PLATFORM
SET linkers=User32.lib Gdi32.lib kernel32.lib winspool.lib comdlg32.lib advapi32.lib Shell32.lib
cl -Zi /W3 /EHsc %defines% %cFilenames% /link %linkers% /out:%name%.exe
REM tags for cl later 
REM Shell32.lib for system tray acces 
popd
ECHO "Building %name%% DONE! Finished!"


REM REM Build script for engine
REM @ECHO OFF
REM SetLocal EnableDelayedExpansion
REM 
REM REM Get a list of all the .c files.
REM SET cFilenames=
REM FOR /R %%f in (*.c) do (
REM     SET cFilenames=!cFilenames! %%f
REM )
REM 
REM REM echo "Files:" %cFilenames%
REM 
REM SET assembly=engine
REM SET compilerFlags=-g -shared -Wvarargs -Wall -Werror
REM REM -Wall -Werror
REM SET includeFlags=-Isrc -I%VULKAN_SDK%/Include
REM SET linkerFlags=-luser32 -lvulkan-1 -L%VULKAN_SDK%/Lib
REM SET defines=-D_DEBUG -DKEXPORT -D_CRT_SECURE_NO_WARNINGS -WINDOWS_PLATFORM
REM 
REM ECHO "Building %assembly%%..."
REM clang %cFilenames% %compilerFlags% -o ../bin/%assembly%.dll %defines% %includeFlags% %linkerFlags%
