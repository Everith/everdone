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
REM DEFINES
SET defines=/D DEBUG 
SET defines=!defines! /D _CONSOLE
SET defines=!defines! /D _UNICODE /D UNICODE
REM INCLUDE
SET includes=/I src
SET includes=!includes! /I %VULKAN_SDK%/Include
SET includes=!includes! /I ../../vendor/glad/Include
SET includes=!includes! /I ../../vendor/glfw-3.3.8.bin.WIN64/include
REM LINKERS
REM Shell32.lib for system tray acces
SET linkers=/link
SET linkers=!linkers! /LIBPATH:%VULKAN_SDK%/Lib vulkan-1.lib
SET linkers=!linkers! /LIBPATH:../../vendor/glfw-3.3.8.bin.WIN64/lib-vc2022 glfw3.lib opengl32.lib
SET linkers=!linkers! User32.lib Gdi32.lib kernel32.lib winspool.lib comdlg32.lib advapi32.lib Shell32.lib
REM SET linkers=!linkers! 

cl /JMC /ZI /W3 /EHsc /MDd /GS /permissive- /Gm- /Od /sdl /Zc:inline /Zc:wchar_t /Zc:forScope /fp:precise /errorReport:prompt /WX- /RTC1 /Gd /FC /std:c++latest %includes% %defines% %cFilenames% %linkers% /out:%name%.exe
REM TODO: Create a list of options
REM /MDd NOTE: needed for openGL glfw and glad for some reason
REM -Zi 
REM -Z7 
REM /Fe"main"  can change name of something
popd
ECHO "Building %name%% DONE! Finished!"