#! /bin/bash
# Build script for engine
set echo on

mkdir -p ../bin

# Get a list of all the .c files.
cFilenames=$(find src/. -type f -name "*.c*")
#echo "Files:" $cFilenames

assembly="engine"
compilerFlags=""
# -fms-extensions 
# -Wall -Werror
includeFlags=""
linkerFlags="-lvulkan -lxcb -lX11 -lX11-xcb -lxkbcommon -L$VULKAN_SDK/lib -L/usr/X11R6/lib"
defines="-D_DEBUG -DKEXPORT -LINUX_PLATFORM"

echo "Building $assembly..."
#clang $cFilenames -o ../bin/lib$assembly.so $defines $includeFlags $linkerFlags
clang src/everdone.cpp -o ../bin/lib$assembly
