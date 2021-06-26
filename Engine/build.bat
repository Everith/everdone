@ECHO OFF

mkdir build
pushd build

cl ..\src\win32_everdone.cpp User32.lib Gdi32.lib kernel32.lib winspool.lib comdlg32.lib advapi32.lib
popd
